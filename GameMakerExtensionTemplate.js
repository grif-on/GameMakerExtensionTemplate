// This file is for HTML5 platform

function GameMakerExtensionTemplate_init() { }

function GameMakerExtensionTemplate_quit() { }

function GameMakerExtensionTemplate_multiply(value) {
  return value * 100;
}

function GameMakerExtensionTemplate_concatenate_string_and_number(heading, value) {
  return heading + value;
}

function GameMakerExtensionTemplate_read_and_fill_buffer(buffer_pointer, size) {
  var view = new Uint8Array(buffer_pointer, 0, size);
  var total = 0;
  for (var i = 0; i < size; i++) {
    total += view[i];
    view[i] = i;
  }

  return "Total = " + total;
}