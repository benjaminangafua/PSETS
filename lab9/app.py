import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")


@app.route("/", methods=["GET", "POST"])
def index():

    name = request.form.get("name")
    month = request.form.get("month") 
    day = request.form.get("day")
    if request.method == "POST":
        # Validate name and sport 
        if not name:
            return render_template("Missing name")

        if not month:
            return render_template("Missing month")

        if  not day:
            return render_template("invalid day")
        
        db.execute("INSERT INTO birthdays (name, month, day) VALUES(?, ?, ?)", name, month, day)
        # TODO: Add the user's entry into the database

        return redirect("/")

    else:

        # TODO: Display the entries in the database on index.html
        celebrants = db.execute("SELECT * FROM birthdays")
    
        return render_template("index.html", celebrants=celebrants)