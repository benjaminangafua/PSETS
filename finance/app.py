import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, jsonify
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached


@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")
# export API_KEY=pk_5dd3c497a8f349afb35628edd13adfc1
# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():

    user_id = session["user_id"]
    stocks = db.execute(f"SELECT * FROM purchase WHERE users_id IN (SELECT id FROM users WHERE id = {user_id})")
    # print(stocks[-1])
    # if stocks != None:{'users_id': 7, 'cost': 156.81, 'cash': 2817.3700000000003, 'balance': 2974.1800000000003,
    #  'share': 1, 'symbol': 'AAPL', 'transaction_time': '2021-11-27 17:17:50'}
    if not stocks:
        return render_template("buy.html")
    purchase = {}
    for stock in stocks:
        purchase["symbol"] = stock["symbol"]
        purchase["share"] = stock["share"]
        purchase["price"] = usd(lookup(str(stock["symbol"]))["price"])
        purchase["name"] = lookup(stock["symbol"])["name"]
        purchase["time"] = stock["transaction_time"]
        purchase["total"] = usd(stock["cost"])

        purchase["cash"] = usd(stock["cash"])
        purchase["balance"] = usd(stock["balance"])

    return render_template("portfolio.html", purchase=purchase)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    # return apology("TODO")

    user_id = session["user_id"]

    if request.method == "POST":
        shares = request.form.get("shares")
        stock = lookup(request.form.get("symbol"))

        if not stock or stock == False:
            return apology("Please input a valid stock", 400)

        if not shares.isdigit() or int(request.form.get("shares")) <= 0:
            return apology("Share was not specified.", 400)

        price = float(stock["price"])

        default_cash = float(db.execute("SELECT cash FROM users WHERE id =?", user_id)[0]["cash"])

        # 1,177.55 COST
        holding = float(price * float(shares))

        # 8, 822.45 CASH
        cashOnHand = default_cash - holding

        # 10,000.00 BALANCE
        totalHolding = cashOnHand + holding
        # print(cashOnHand, holding)

        if holding > cashOnHand:
            return apology("Sorry!! Low balance", 400)

        # update user's cash
        db.execute(f"UPDATE users SET cash = {cashOnHand} WHERE id = {user_id}")

        # Render an apology, without completing a purchase, if the user cannot afford the number of shares at the current price.
        # Store enough information so that you know who bought what at what price and when.
        db.execute(
            "INSERT INTO  purchase (users_id, cost, cash, balance, share, symbol, transaction_time) VALUES(?, ?, ?, ?,?, ?, datetime('now'))",
            user_id, holding, cashOnHand, totalHolding, int(shares), stock["symbol"])

        # When a purchase is complete, redirect the user back to the index page.
        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    # return apology("TODO")

    user_id = session["user_id"]

    buys = db.execute(f"SELECT * FROM purchase WHERE users_id IN (SELECT id FROM users WHERE id = {user_id})")

    sold = {}
    sell = db.execute(f"SELECT * FROM sell WHERE users_id IN (SELECT id FROM users WHERE id = {user_id})")

    if not sell:
        return redirect("/")

    if not buys:
        return redirect("/")

    for sale in sell:
        sold["share"] = sale["sold_share"]
        sold["price"] = usd(sale["price"])
        sold["time"] = sale["transaction_time"]
        sold["symbol"] = sale["symbol"]
        sold["name"] = lookup(sale["symbol"])["name"]

    purchase = {}
    for buy in buys:
        purchase["symbol"] = buy["symbol"]
        purchase["share"] = buy["share"]
        purchase["cash"] = usd(buy["cash"])
        purchase["time"] = buy["transaction_time"]
        purchase["name"] = lookup(buy["symbol"])["name"]

    # Share of the number of stock sole
    return render_template("history.html", purchase=purchase, sold=sold)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")

# TODO for QUOTE


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    stock = request.form.get("symbol")
    symbol = lookup(str(stock))
    if request.method == "POST":

        if not symbol or symbol == False:
            return apology("Symbol not specified", 400)
        else:
            return render_template("quoted.html", symbol=symbol)
    else:
        # return jsonify()
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # Get user info
    username = request.form.get("username")
    password = request.form.get("password")
    confirmation_pwd = request.form.get("confirmation")
    rows = db.execute("SELECT * FROM users WHERE username = ?", username)
    user = validateUser(rows)
    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not username:
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not password:
            return apology("must provide password", 400)

        # confirm password was submitted
        elif confirmation_pwd != password:
            return apology("Password not match", 400)

         # Remove duplicate users.
        elif user == username:
            return apology("Username already exist", 400)
        else:
            # submit registration
            db.execute("INSERT INTO  users (username, hash ) VALUES(?, ?)", username,
                       generate_password_hash(password, method='pbkdf2:sha256', salt_length=8))
            # Redirect user to login page
            return redirect("/login")
    else:
        # Send registration page
        return render_template("register.html")


def validateUser(rows):
    for index in range(len(rows)):
        return rows[index]["username"]


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    # return apology("TODO")
    user_id = session["user_id"]
    if request.method == "POST":

        # input from form
        sharesInput = int(request.form.get("shares"))

        symbols = lookup(request.form.get("symbol"))

        # validate form's input
        if not symbols or symbols == False:
            return apology("Please input a valid symbols", 400)

        if sharesInput is None:
            return apology("Share was not specified.", 400)

        price = float(symbols["price"])

        # Query finance db for share
        sharedb = db.execute("SELECT share FROM purchase WHERE users_id=:id  ORDER BY transaction_time DESC",
                             id=user_id)[0]["share"]

        # Balance in DB
        cashInDb = float(db.execute("SELECT cash FROM users WHERE id =?",
                                    user_id)[0]["cash"])

        # Check if user own a share
        if sharesInput > sharedb:
            return apology("Sorry your share does not match", 400)

        # sell share remain
        shares = int(sharedb) - sharesInput

        # selling price of a given number of shares
        totalCost = shares * price

        # Cash title under total
        totalCash = cashInDb - totalCost

        # cash to go in db
        cash = totalCost + cashInDb

        # outstanding balance in users table
        if not cash and not totalCash:
            return apology("Account is empty", 400)

        db.execute(f"UPDATE users SET cash = {cash} WHERE id = {user_id}")
        db.execute(f"UPDATE purchase SET cash = {totalCash} WHERE users_id = {user_id}")

        # totalcost, cash_balance for profolio of a sale made
        db.execute("INSERT INTO sell (users_id, sold_share, share, price, symbol, totalCost, balance,cash, transaction_time) VALUES (?, ?, ?, ?, ?, ?, ?, ?, datetime('now'))",
                   user_id, sharesInput, shares, price, symbols["symbol"], totalCost, totalCash, cash)

        # return render_template("sold.html", symbols=symbols, shares=shares)
        stocks = db.execute(f"SELECT * FROM sell WHERE users_id IN (SELECT id FROM users WHERE id = {user_id})")
        print(f"==========>>>>>>>>>{stocks}")

        if not stocks:
            return render_template("buy.html")

        purchase = {}
        for stock in stocks:
            purchase["symbol"] = stock["symbol"]
            purchase["share"] = stock["share"]

            purchase["price"] = usd(lookup(str(stock["symbol"]))["price"])
            purchase["name"] = lookup(stock["symbol"])["name"]
            purchase["time"] = stock["transaction_time"]
            purchase["total"] = usd(stock["totalCost"])

            purchase["cash"] = usd(stock["cash"])
            purchase["balance"] = usd(stock["balance"])

        return render_template("portfolio.html", purchase=purchase)

    else:
        symbols = db.execute("SELECT DISTINCT(symbol) FROM purchase WHERE users_id=:id", id=user_id)
        return render_template("sell.html", symbols=symbols)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)


# postgres://nrzkrpdladeyjy:38050aa3b82d5d6d884832c86899572741f3c6445f956fa501c1037f523f1e6a@ec2-3-230-219-251.compute-1.amazonaws.com:5432/d1ca24pj48gv0c