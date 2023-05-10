Module.onRuntimeInitialized = () => { start(); }

var g;

const kanjiB = new Image();
const kanjiN = new Image();
const kanjiBIM = new Image();
const kanjiNIM = new Image();
const emptycase = new Image();
const errorcase = new Image();
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

function canvasLeftClick(event) {
    var x = event.pageX - canvas.offsetLeft;
    var y = event.pageY - canvas.offsetTop;
    var squareSize = canvas.width / Module._nb_cols(g);
    var row = Math.floor(y / squareSize);
    var col = Math.floor(x / squareSize);
    var square = (Module._get_square(g, row, col) + 1) %3;
    Module._play_move(g, row, col, square);
    printGame(g);
}

window.addEventListener('resize', function(){
    resizeCanvas();
    printGame(g);
}  ); 

function resizeCanvas() {
    const minSize = Math.min(window.innerWidth, window.innerHeight);
    canvas.width = minSize * 0.7;
    canvas.height = canvas.width;
  }

function printGame(g) {
    var nb_rows = Module._nb_rows(g);
    var nb_cols = Module._nb_cols(g);
    resizeCanvas();
    var squareSize = canvas.width / nb_cols;
    for (var row = 0; row < nb_rows; row++) {
        for (var col = 0; col < nb_cols; col++) {
            var number = Module._get_number(g, row, col);
            var immutable = Module._is_immutable(g, row, col);
            var empty = Module._is_empty(g, row, col);
            var error = Module._has_error(g, row, col);
            if (empty)
            {
                if (error){
                    ctx.drawImage(errorcase,  col*squareSize, row*squareSize, squareSize, squareSize);
                }else{
                ctx.drawImage(emptycase,  col*squareSize, row*squareSize, squareSize, squareSize);
            }}

            else if (immutable && number == 0)
            {
                if (error){
                    ctx.drawImage(errorcase,  col*squareSize, row*squareSize, squareSize, squareSize);
                }else{
                ctx.drawImage(kanjiBIM,  col*squareSize, row*squareSize, squareSize, squareSize);
            }}

            else if (immutable && number == 1)
            {
                if (error){
                    ctx.drawImage(errorcase,  col*squareSize, row*squareSize, squareSize, squareSize);
                }else{
                ctx.drawImage(kanjiNIM,  col*squareSize, row*squareSize, squareSize, squareSize);
            }}

            else if (number == 0)
            {
                if (error){
                    ctx.drawImage(errorcase,  col*squareSize, row*squareSize, squareSize, squareSize);
                }else{
                ctx.drawImage(kanjiB,  col*squareSize, row*squareSize, squareSize, squareSize);
            }}

            else if (number == 1)
            {
                if (error){
                    ctx.drawImage(errorcase,  col*squareSize, row*squareSize, squareSize, squareSize);
                }else{
                ctx.drawImage(kanjiN,  col*squareSize, row*squareSize, squareSize, squareSize);
            }}

            else 
            {
                if (error){
                    ctx.drawImage(errorcase,  col*squareSize, row*squareSize, squareSize, squareSize);
                }else{
                ctx.drawImage(emptycase,  col*squareSize, row*squareSize, squareSize, squareSize);
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
errorcase.src = 'ressources/erreur.png';