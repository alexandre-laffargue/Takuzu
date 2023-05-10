Module.onRuntimeInitialized = () => { start(); }

function printGame(g) {
    var text = "";
    var nb_rows = Module._nb_rows(g);
    var nb_cols = Module._nb_cols(g);
    for (var row = 0; row < nb_rows; row++) {
        for (var col = 0; col < nb_cols; col++) {
            var number = Module._get_number(g, row, col);
            var immutable = Module._is_immutable(g, row, col);
            var empty = Module._is_empty(g, row, col);
            // var error = Module._has_error(g, row, col);
            if (empty)
                text += " ";
            else if (immutable && number == 0)
                text += "W";
            else if (immutable && number == 1)
                text += "B";
            else if (number == 0)
                text += "w";
            else if (nummber == 1)
                text += "b";
            else text += "?";
        }
        text += "\n";
    }

    // put this text in <div> element with ID 'result'
    var elm = document.getElementById('result');
    elm.innerHTML = text;
}

function start() {
    console.log("call start routine");
    var g = Module._new_default();
    const LIGHTBULB = 1;
    Module._play_move(g, 0, 0, LIGHTBULB);
    printGame(g);
    Module._delete(g);
}

var canvas = document.getElementById('mycanvas');

/* ******************** register events ******************** */

window.addEventListener('load', windowLoad);              // window load
canvas.addEventListener('click', canvasLeftClick);        // left click event
canvas.addEventListener('contextmenu', canvasRightClick); // right click event

/* ******************** event callback ******************** */

function canvasLeftClick(event) {
    event.preventDefault(); // prevent default context menu to appear...
    // get relative cursor position in canvas
    console.log("left click at position:", event.offsetX, event.offsetY);
    // update position of mario image used by drawCanvas()
    marioX = event.offsetX;
    marioY = event.offsetY;
    drawCanvas();
}

function canvasRightClick(event) {
    event.preventDefault(); // prevent default context menu to appear...
    // get relative cursor position in canvas
    console.log("right click at position:", event.offsetX, event.offsetY);
    // update position of mario image used by drawCanvas()
    squareX = event.offsetX;
    squareY = event.offsetY;
    drawCanvas();
}

function windowLoad() {
    console.log("window load");
    drawCanvas();
}

/* ******************** canvas drawing ******************** */

function drawCanvas() {
    var ctx = canvas.getContext('2d');
    var width = canvas.width;
    var height = canvas.height;

    // clear canvas
    ctx.clearRect(0, 0, width, height);

    // draw a yellow square at (squareX, squareY) position
    ctx.save();
    ctx.fillStyle = 'yellow';
    ctx.fillRect(squareX, squareY, 40, 40);
    ctx.restore();

    // draw some lines
    ctx.save();
    ctx.strokeStyle = 'blue';
    ctx.moveTo(0, 0);
    ctx.lineTo(width, height);
    ctx.moveTo(width, 0);
    ctx.lineTo(0, height);
    ctx.stroke(); // the stroke will actually paint the current lines
    ctx.restore();

    // draw a centered text
    ctx.save();
    ctx.font = 'bold 20px Arial';
    ctx.fillStyle = 'black';
    ctx.textBaseline = 'middle';
    ctx.textAlign = 'center';
    ctx.fillText("Hello World!", width / 2, height / 2);
    ctx.restore();

    // draw mario image at (marioX, marioY) position
    ctx.drawImage(mario, marioX, marioY, 80, 80);
}

