// **********************************************************************************************************************
//
// Copyright (c)2014, YoYo Games Ltd. All Rights reserved.
// Copyright (c)2026, Grif_on - all edits are considered public domain
//
// Authors:         Mike.Dailly and Grif_on
// Project:         GameMaker Extension Template
// Description:     Shows the basics of creating an extension.
//
//                  Please also take a note that you can use POST build event.
//                  Once compiled library added to a project, get the full name+path of it and make sure
//                  you copy over it every time you re-build library - debug AND release!
//
// Date             Version     BY         Comment
// ----------------------------------------------------------------------------------------------------------------------
// 23/06/2014       V1.0        MJD        1st verison
// 23/02/2026       V1.1        Grif_on    Refactored and formatted
//
// **********************************************************************************************************************

#include <stdio.h>
#include <string.h>

#if defined(_MSC_VER)
  #define DLL_EXPORT __declspec(dllexport)
  #define snprintf   sprintf_s
  #define strdup     _strdup
#else
  #define DLL_EXPORT __attribute__((visibility("default")))
#endif

// Ensure that the symbols are unmangled in the dynamic lib
extern "C" {

  static bool g_initialised = false;

  /**
   * Example on how to make "Initialise the DLL" function.
   * NOTE: in TestProject.yyp calling of this function as "init" already set up (inside extension asset).
   *
   */
  DLL_EXPORT void GameMakerExtensionTemplate_init() {
    g_initialised = true;
  }

  /**
   * Example on how to make "Shutdown the DLL" function.
   * NOTE: in TestProject.yyp calling of this function as "final" already set up (inside extension asset).
   *
   */
  DLL_EXPORT void GameMakerExtensionTemplate_quit() {
    g_initialised = false;
  }

  /**
   * Takes a double... returns this double multiplied by 100.
   *
   * @param value A user value.
   *
   * @return A value * 100.0
   */
  DLL_EXPORT double GameMakerExtensionTemplate_multiply(double value) {
    if (!g_initialised) return 0.0;
    return value * 100.0;
  }

  /**
   * Takes a string and a number... return a new string that have number at the end of it.
   * NOTE: strings are UTF8 (demo is in ASCI, all chars <128).
   *
   * @param text  A user heading prefix string.
   * @param value A user number.
   *
   * @return Concatenation of string and number.
   */
  DLL_EXPORT char* GameMakerExtensionTemplate_concatenate_string_and_number(const char* text, double value) {
    if (!g_initialised) return NULL;

    char s[1024];
    snprintf(&s[0], 1023, "%s%f", text, (float)value);
    char* p_string = strdup(s);
    return p_string;
  }

  /**
   * This example takes a GML buffer pointer, adds up the data contained in it,
   * then fills in some NEW data. Please note never go beyond the bounds
   * of the buffer, and never free/realloc it. GML controls it's life.
   *
   * @param p_buffer Buffer pointer.
   * @param size     The size of buffer in bytes.
   *
   * @return String holding the total of the data. Buffer data is also changed.
   */
  DLL_EXPORT char* GameMakerExtensionTemplate_read_and_fill_buffer(void* p_buffer, double size) {
    if (!g_initialised) return NULL;

    unsigned char* p_char_buffer = (unsigned char*)p_buffer;
    int i, total = 0;
    for (i = 0; i < size; i++) {
      total += p_char_buffer[i];            // buffer read example
      p_char_buffer[i] = (unsigned char)i;  // buffer write example
    }

    char s[1024];
    snprintf(&s[0], 1023, "Total = %d", total);
    char* pString = strdup(s);
    return pString;
  }

}  // extern "C"
