let data = []
let prevMouseX, prevMouseY;
let max = 1.0

let position = 0
let dataCount = 0

let buffer

// let dpr
// if(window.devicePixelRatio !== undefined) {
//     dpr = window.devicePixelRatio;
// } else {
//     dpr = 1;
// }

let w = window.innerWidth
let h = window.innerHeight

function progressBar() {
  // fill('black')
  // rect(0,0, displayWidth, 42)
  // fill('white')
  // textAlign('left')
  // text(map(position, 0, dataCount, 0, displayWidth), 10, 30)
  fill('red')
  stroke('black')  
  rect(0,0,map(position, 0, dataCount, 0, w)-1, 5)
}

function preload() {
  loadJSON('data.json', ({
    values
  }) => {
    // shave off the first 10k data points; all zero
    data = values.slice(10000, -1)
    // data = data.filter(v => v > 0)
    max = data.reduce((m, value) => m > value ? m : value, 0)
    data = data.map(v => map(v, 0, max, 0, 1))
    dataCount = data.length
  })
}

function setup() {
  buffer = createCanvas(w, h);
  console.log(data.length)
  prevMouseX = mouseX
  prevMouseY = mouseY
  background(0);
  console.log(w, h)
  
  reset = createButton('reset');
  reset.position(w - 50, 10);
  reset.mousePressed(resetSketch);
  reset = createButton('save');
  reset.position(w - 120, 10);
  reset.mousePressed(snapshot);
}

function snapshot() {
  saveCanvas(buffer, 'myCanvas', 'jpg');
}

function resetSketch() {
  prevMouseX = mouseX
  prevMouseY = mouseY
  background(0)
  position = 0
}

function draw() {
  //background(220);
  if (position == 0) {
    fill('white')
    textAlign('center')
    textSize(32)
    text('Draw Here…', w/2, h/2)
  }
}

function keyPressed({key}) {
  console.log(key)
  switch(key) {
    case 'r':
      resetSketch();
      break;
  }
}

function mousePressed() {
  prevMouseX = mouseX
  prevMouseY = mouseY
}

function mouseDragged() {
  if (position > dataCount) return
  if (position == 0) background(0)

  let from = createVector(prevMouseX, prevMouseY)
  let to = createVector(mouseX, mouseY)
  let dst = from.dist(to)

  if (dst < 1.0) return

  for (let i = 0; i < Math.round(dst); i) {
    let s = map(data[position % dataCount], 0, 1, 42, 255)
    let d = map(data[position % dataCount], 0, 1, 0.5, 20)
    stroke(s)
    fill(s)
    position += 1
    strokeWeight(1)
    let v = from.lerp(to, i / dst)
    ellipse(v.x, v.y, d, d)
    fill(255 - s)
    rect(10, 10, 10, 10)
    i += d
  }

  prevMouseX = mouseX
  prevMouseY = mouseY

  progressBar()
}