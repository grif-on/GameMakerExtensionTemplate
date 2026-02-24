function MyExtension_Init() { }

function MyExtension_Quit() { }

function MyExtension_Function(value) {
  return value * 100;
}

function MyExtension_StringReturn(heading, value) {
  return heading + value;
}

function MyExtension_BufferPointer(buffer_pointer, size) {
  var view = new Uint8Array(buffer_pointer, 0, size);
  var total = 0;
  for (var i = 0; i < size; i++) {
    total += view[i];
    view[i] = i;
  }

  return "Total = " + total;
}