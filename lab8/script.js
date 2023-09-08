// let acon = confirm("Hello");
// greet=()=>{
//     let name = document.querySelector("input[type=text]").value
//     confirm(`Hello, ${name}`)
// }
// function name()



/** Page DOMContentLoaded
 * document.addEventListener("DOMContentLoaded", ()=>{
    document.querySelector("form").addEventListener("submit", ()=>{
        let today = new Date().getFullYear();
        let name = document.querySelector("input[type=text]").value;
        confirm(`Hello, ${name} is drinking ${today} tea.`)
    });
    });
*
*/

/**On input
 * document.addEventListener("DOMContentLoaded", ()=>{
    let input = document.querySelector("input");
    input.addEventListener("keyup", (event)=>{
        let name = document.querySelector("#name");
        
        if(input.value){

            name.innerHTML = `Hello, ${input.value} is drinking tea.`;
        }
        else{
            name.innerHTML = `Hello whoever you are.`
        }
    }) 
});
 *  */ 

// document.querySelector("form").addEventListener("submit", greet)