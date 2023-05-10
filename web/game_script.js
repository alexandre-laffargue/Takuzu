Module.onRuntimeInitialized = () => { start(); }

const canvas = document.getElementById('canvas');
const ctx = canvas.getContext('2d');
ctx.font = "20px Arial";
ctx.fillStyle = "red";



function printGame(g) {
    var text = "";
    var nb_rows = Module._nb_rows(g);
    var nb_cols = Module._nb_cols(g);
    for (var row = 0; row < nb_rows; row++) {
        for (var col = 0; col < nb_cols; col++) {
            var number = Module._get_number(g, row, col);
            var immutable = Module._is_immutable(g, row, col);
            var empty = Module._is_empty(g, row, col);
            var error = Module._has_error(g, row, col);
            if (empty){
                text = "";
                ctx.fillText(text, col*30, row * 30);
            }
                else if (immutable && number == 0)
            {
                text = "W";
                ctx.fillText(text, col*30, row * 30);
            }
            else if (immutable && number == 1)
            {
                text = "B";
                ctx.fillText(text, col*30, row * 30);
            }
            else if (number == 0)
            {
                text = "w";
                ctx.fillText(text, col*30, row * 30);
            }
            else if (nummber == 1)
            {
                text = "b";
                ctx.fillText(text, col*30, row * 30);
            }
            else 
            {
                text = "?";
                ctx.fillText(text, col*30, row * 30);
            }
        }
        
        text = "";
    }
    
    
}

function start() {
    console.log("call start routine");
    var g = Module._new_default();
    const LIGHTBULB = 1;
    Module._play_move(g, 0, 0, LIGHTBULB);
    printGame(g);
    Module._delete(g);
}



