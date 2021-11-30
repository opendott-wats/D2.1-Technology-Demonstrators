let data = []
let prevMouseX, prevMouseY;
let max = 1.0

let position = 0
let dataCount = 0

function preload() {
  loadJSON('data.json', ({values}) => {
    data = values
    // data = data.filter(v => v > 0)
    max = data.reduce((m, value) => m > value ? m : value, 0)
    data = data.map(v => map(v, 0, max, 0, 1))
    dataCount = data.length
  })
}

function setup() {
  createCanvas(400, 400);
  console.log(data.length)
  prevMouseX = mouseX
  prevMouseY = mouseY
  background(0);
}

function draw() {
  //background(220);
}

function mousePressed() {
  prevMouseX = mouseX
  prevMouseY = mouseY
}


function rangeOf(from, to) {
  if (from < to) {
    return Array.from({ length: to - from + 1 }, (_, i) => from + i)
  } else {
    return Array.from({ length: from - to + 1}, (_, i) => to + i)
  }
}

function mouseDragged() {
  // let dX = rangeOf(prevMouseX, mouseX)
  // let dY = rangeOf(prevMouseY, mouseY)
  let from = createVector(prevMouseX, prevMouseY)
  let to = createVector(mouseX, mouseY)
  let d = from.dist(to)

  if (d < 1.0) return

  for (let i = 0; i < Math.round(d); i++) {
      // console.log(position%dataCount, position, dataCount, data.length)
    let s = map(data[position%dataCount], 0, 1, 1, 255)
    position += 1
      stroke(map(s, 0,255, 100, 255))
      position += 1
      strokeWeight(map(s, 0, 255, 1, 5))
    let v = from.lerp(to, i/d)
    point(v.x, v.y)
    fill(255-s)
  }
  
  // dX.forEach(x => {
  //   dY.forEach(y => {
  //     position += 1
  //     console.log(position)
  //     stroke(map(data[position], 0, 1, 127, 255))
  //     strokeWeight(1)
  //     point(x, y)
  //   })
  // })
  
  
  prevMouseX = mouseX
  prevMouseY = mouseY

}