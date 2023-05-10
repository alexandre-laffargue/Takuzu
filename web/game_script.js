Module.onRuntimeInitialized = () => { start(); }

var g;

const kanjiB = new Image();
const kanjiN = new Image();
const kanjiBIM = new Image();
const kanjiNIM = new Image();
const emptycase = new Image();
const canvas = document.getElementById('canvas');
const ctx = canvas.getContext('2d');

var btnrestart = document.getElementById("restart");
var btnsolve = document.getElementById("solve");
var btnundo = document.getElementById("undo");
var btnredo = document.getElementById("redo");
var btnrandom = document.getElementById("random");


btnrestart.addEventListener("click", function() {
    Module._restart(g);
    printGame(g);
});

btnsolve.addEventListener("click", function() {
    Module._solve(g);
    printGame(g);
});

btnundo.addEventListener("click", function() {
    Module._undo(g);
    printGame(g);
});

btnredo.addEventListener("click", function() {
    Module._redo(g);
    printGame(g);
});

btnrandom.addEventListener("click", function() {
    g = Module._game_random(6, 6, false, false, true);
    printGame(g);
});


function printGame(g) {
    var text = "";
    var nb_rows = Module._nb_rows(g);
    var nb_cols = Module._nb_cols(g);
    canvas.width = nb_cols * 50;
    canvas.height = nb_rows * 50;
    for (var row = 0; row < nb_rows; row++) {
        for (var col = 0; col < nb_cols; col++) {
            var number = Module._get_number(g, row, col);
            var immutable = Module._is_immutable(g, row, col);
            var empty = Module._is_empty(g, row, col);
            var error = Module._has_error(g, row, col);
            if (empty){
                text = "";
                ctx.drawImage(emptycase, col*50, row * 50, 50, 50);
            }
                else if (immutable && number == 0)
            {
                text = "W";
                ctx.drawImage(kanjiBIM, col*50, row * 50, 50, 50);
            }
            else if (immutable && number == 1)
            {
                text = "B";
                ctx.drawImage(kanjiNIM, col*50, row * 50, 50, 50);
            }
            else if (number == 0)
            {
                text = "w";
                ctx.drawImage(kanjiB, col*50, row * 50, 50, 50);
            }
            else if (number == 1)
            {
                text = "b";
                ctx.drawImage(kanjiN, col*50, row * 50, 50, 50);
            }
            else 
            {
                text = "?";
                ctx.drawImage(empty, col*50, row * 50, 50, 50);
            }
        }
        
        text = "";
    }
    
    
}

function start() {
    console.log("call start routine");
    g = Module._new_default();
    printGame(g);
}


kanjiB.src = 'ressources/kanjiB.png';
kanjiN.src = 'ressources/kanjiN.png';
kanjiBIM.src = 'ressources/kanjiBIM.png';
kanjiNIM.src = 'ressources/kanjiNIM.png';
emptycase.src = 'ressources/empty.png';