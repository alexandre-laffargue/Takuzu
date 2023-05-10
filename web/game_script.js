Module.onRuntimeInitialized = () => { start(); }

var g;

const kanjiB = new Image();
const kanjiN = new Image();
const kanjiBIM = new Image();
const kanjiNIM = new Image();
const emptycase = new Image();
const error = new Image();
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
    g = Module._new_random(6, 6, false, false);
    printGame(g);
});

canvas.addEventListener("click", canvasLeftClick);
canvas.addEventListener("contextmenu", canvasRightClick);

function canvasLeftClick(event) {
    var x = event.pageX - canvas.offsetLeft;
    var y = event.pageY - canvas.offsetTop;
    var row = Math.floor(y / 50);
    var col = Math.floor(x / 50);
    Module._play_move(g, row, col, 1);
    printGame(g);
}

function canvasRightClick(event) {
    event.preventDefault();
    var x = event.pageX - canvas.offsetLeft;
    var y = event.pageY - canvas.offsetTop;
    var row = Math.floor(y / 50);
    var col = Math.floor(x / 50);
    Module._play_move(g, row, col, 2);
    printGame(g);
}

function printGame(g) {
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
            if (empty)
            {
                if (error){
                    ctx.drawImage(error, col*50, row * 50, 50, 50);
                }else{
                ctx.drawImage(emptycase, col*50, row * 50, 50, 50);
            }}

            else if (immutable && number == 0)
            {
                if (error){
                    ctx.drawImage(error, col*50, row * 50, 50, 50);
                }else{
                ctx.drawImage(kanjiBIM, col*50, row * 50, 50, 50);
            }}

            else if (immutable && number == 1)
            {
                if (error){
                    ctx.drawImage(error, col*50, row * 50, 50, 50);
                }else{
                ctx.drawImage(kanjiNIM, col*50, row * 50, 50, 50);
            }}

            else if (number == 0)
            {
                if (error){
                    ctx.drawImage(error, col*50, row * 50, 50, 50);
                }else{
                ctx.drawImage(kanjiB, col*50, row * 50, 50, 50);
            }}

            else if (number == 1)
            {
                if (error){
                    ctx.drawImage(error, col*50, row * 50, 50, 50);
                }else{
                ctx.drawImage(kanjiN, col*50, row * 50, 50, 50);
            }}

            else 
            {
                if (error){
                    ctx.drawImage(error, col*50, row * 50, 50, 50);
                }else{
                ctx.drawImage(empty, col*50, row * 50, 50, 50);
            }}
            
        }
        
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
error.src = 'ressources/error.png';