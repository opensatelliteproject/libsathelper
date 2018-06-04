/*
 * TermColor.h
 *
 *  Created on: 08/09/2017
 *      Author: Lucas Teske
 *      Originally from: (Joel Sjogren) https://stackoverflow.com/questions/2616906/how-do-i-output-coloured-text-to-a-linux-terminal
 */

#ifndef SRC_TERMCOLOR_H_
#define SRC_TERMCOLOR_H_

#include <ostream>
namespace SatHelper {
    enum Modifier : unsigned int {
        DEFAULT       =      0,
        BOLD          =      1,
        DIM           =      2,
        ITALIC        =      3,
        UNDERLINE     =      4,
        INVERSE       =      7,
        HIDDEN        =      8,
        STRIKETHROUGH =      9,

        BLACK         =     30,
        RED           =     31,
        GREEN         =     32,
        YELLOW        =     33,
        BLUE          =     34,
        MAGENTA       =     35,
        CYAN          =     36,
        WHITE         =     37,
        GRAY          =     90,
        GREY          =     90,

        BG_BLACK      =     40,
        BG_RED        =     41,
        BG_GREEN      =     42,
        BG_YELLOW     =     44,
        BG_BLUE       =     44,
        BG_MAGENTA    =     45,
        BG_CYAN       =     46,
        BG_WHITE      =     47,
        BG_DEFAULT    =     49,
    };
    class TermColor {
        static bool ColorEnabled;
        Modifier code;
    public:
        TermColor(Modifier pColor) : code(pColor) {}
        friend std::ostream&
        operator<<(std::ostream& os, const TermColor& mod) {
          if (ColorEnabled) {
            return os << "\033[" << mod.code << "m";
          } else {
            return os;
          }
        }
    };

  static TermColor c_bold(Modifier::BOLD);
  static TermColor c_italic(Modifier::ITALIC);
  static TermColor c_dim(Modifier::DIM);
  static TermColor c_underline(Modifier::UNDERLINE);
  static TermColor c_inverse(Modifier::INVERSE);
  static TermColor c_hidden(Modifier::HIDDEN);
  static TermColor c_strikethrough(Modifier::STRIKETHROUGH);
  static TermColor c_default(Modifier::DEFAULT);

  static TermColor c_input(Modifier::GREY);
  static TermColor c_verbose(Modifier::CYAN);
  static TermColor c_prompt(Modifier::GREY);
  static TermColor c_info(Modifier::GREEN);
  static TermColor c_data(Modifier::GREY);
  static TermColor c_help(Modifier::CYAN);
  static TermColor c_warn(Modifier::YELLOW);
  static TermColor c_debug(Modifier::BLUE);
  static TermColor c_error(Modifier::RED);
} /* namespace SatHelper */

#define tcendl c_default << std::endl
#define tcarg(x) c_bold << c_warn << x << c_default

#endif /* SRC_TERMCOLOR_H_ */