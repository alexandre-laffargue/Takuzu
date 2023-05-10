Module.onRuntimeInitialized = () => { start(); }

const kanjiB = new Image();
const kanjiN = new Image();
const kanjiBIM = new Image();
const kanjiNIM = new Image();
const emptycase = new Image();
const canvas = document.getElementById('canvas');
const ctx = canvas.getContext('2d');




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
    var g = Module._new_default();
    const LIGHTBULB = 1;
    Module._play_move(g, 0, 0, LIGHTBULB);
    printGame(g);
    Module._delete(g);
}


kanjiB.src = 'ressources/kanjiB.png';
kanjiN.src = 'ressources/kanjiN.png';
kanjiBIM.src = 'ressources/kanjiBIM.png';
kanjiNIM.src = 'ressources/kanjiNIM.png';
emptycase.src = 'ressources/empty.png';