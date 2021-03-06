// Most of this code is borrowed from:
// Markus Kuhn -- 2007-05-26 (Unicode 5.0)
// Latest version: http://www.cl.cam.ac.uk/~mgk25/ucs/wcwidth.c
// Thanks you!
//
// Modified by Arthur Sonzogni for FTXUI.

#include "ftxui/screen/string.hpp"

#include <array>    // for array
#include <codecvt>  // for codecvt_utf8_utf16
#include <cstdint>  // for uint32_t, uint8_t
#include <locale>   // for wstring_convert
#include <string>   // for string, basic_string, wstring

#include "ftxui/screen/deprecated.hpp"  // for wchar_width, wstring_width

namespace {

struct Interval {
  uint32_t first;
  uint32_t last;
};

// Sorted list of non-overlapping intervals of non-spacing characters
// generated by "uniset +cat=Me +cat=Mn +cat=Cf -00AD +1160-11FF +200B c"
const std::array<Interval, 142> g_combining_characters = {
    Interval{0x0300, 0x036F},   Interval{0x0483, 0x0486},
    Interval{0x0488, 0x0489},   Interval{0x0591, 0x05BD},
    Interval{0x05BF, 0x05BF},   Interval{0x05C1, 0x05C2},
    Interval{0x05C4, 0x05C5},   Interval{0x05C7, 0x05C7},
    Interval{0x0600, 0x0603},   Interval{0x0610, 0x0615},
    Interval{0x064B, 0x065E},   Interval{0x0670, 0x0670},
    Interval{0x06D6, 0x06E4},   Interval{0x06E7, 0x06E8},
    Interval{0x06EA, 0x06ED},   Interval{0x070F, 0x070F},
    Interval{0x0711, 0x0711},   Interval{0x0730, 0x074A},
    Interval{0x07A6, 0x07B0},   Interval{0x07EB, 0x07F3},
    Interval{0x0901, 0x0902},   Interval{0x093C, 0x093C},
    Interval{0x0941, 0x0948},   Interval{0x094D, 0x094D},
    Interval{0x0951, 0x0954},   Interval{0x0962, 0x0963},
    Interval{0x0981, 0x0981},   Interval{0x09BC, 0x09BC},
    Interval{0x09C1, 0x09C4},   Interval{0x09CD, 0x09CD},
    Interval{0x09E2, 0x09E3},   Interval{0x0A01, 0x0A02},
    Interval{0x0A3C, 0x0A3C},   Interval{0x0A41, 0x0A42},
    Interval{0x0A47, 0x0A48},   Interval{0x0A4B, 0x0A4D},
    Interval{0x0A70, 0x0A71},   Interval{0x0A81, 0x0A82},
    Interval{0x0ABC, 0x0ABC},   Interval{0x0AC1, 0x0AC5},
    Interval{0x0AC7, 0x0AC8},   Interval{0x0ACD, 0x0ACD},
    Interval{0x0AE2, 0x0AE3},   Interval{0x0B01, 0x0B01},
    Interval{0x0B3C, 0x0B3C},   Interval{0x0B3F, 0x0B3F},
    Interval{0x0B41, 0x0B43},   Interval{0x0B4D, 0x0B4D},
    Interval{0x0B56, 0x0B56},   Interval{0x0B82, 0x0B82},
    Interval{0x0BC0, 0x0BC0},   Interval{0x0BCD, 0x0BCD},
    Interval{0x0C3E, 0x0C40},   Interval{0x0C46, 0x0C48},
    Interval{0x0C4A, 0x0C4D},   Interval{0x0C55, 0x0C56},
    Interval{0x0CBC, 0x0CBC},   Interval{0x0CBF, 0x0CBF},
    Interval{0x0CC6, 0x0CC6},   Interval{0x0CCC, 0x0CCD},
    Interval{0x0CE2, 0x0CE3},   Interval{0x0D41, 0x0D43},
    Interval{0x0D4D, 0x0D4D},   Interval{0x0DCA, 0x0DCA},
    Interval{0x0DD2, 0x0DD4},   Interval{0x0DD6, 0x0DD6},
    Interval{0x0E31, 0x0E31},   Interval{0x0E34, 0x0E3A},
    Interval{0x0E47, 0x0E4E},   Interval{0x0EB1, 0x0EB1},
    Interval{0x0EB4, 0x0EB9},   Interval{0x0EBB, 0x0EBC},
    Interval{0x0EC8, 0x0ECD},   Interval{0x0F18, 0x0F19},
    Interval{0x0F35, 0x0F35},   Interval{0x0F37, 0x0F37},
    Interval{0x0F39, 0x0F39},   Interval{0x0F71, 0x0F7E},
    Interval{0x0F80, 0x0F84},   Interval{0x0F86, 0x0F87},
    Interval{0x0F90, 0x0F97},   Interval{0x0F99, 0x0FBC},
    Interval{0x0FC6, 0x0FC6},   Interval{0x102D, 0x1030},
    Interval{0x1032, 0x1032},   Interval{0x1036, 0x1037},
    Interval{0x1039, 0x1039},   Interval{0x1058, 0x1059},
    Interval{0x1160, 0x11FF},   Interval{0x135F, 0x135F},
    Interval{0x1712, 0x1714},   Interval{0x1732, 0x1734},
    Interval{0x1752, 0x1753},   Interval{0x1772, 0x1773},
    Interval{0x17B4, 0x17B5},   Interval{0x17B7, 0x17BD},
    Interval{0x17C6, 0x17C6},   Interval{0x17C9, 0x17D3},
    Interval{0x17DD, 0x17DD},   Interval{0x180B, 0x180D},
    Interval{0x18A9, 0x18A9},   Interval{0x1920, 0x1922},
    Interval{0x1927, 0x1928},   Interval{0x1932, 0x1932},
    Interval{0x1939, 0x193B},   Interval{0x1A17, 0x1A18},
    Interval{0x1B00, 0x1B03},   Interval{0x1B34, 0x1B34},
    Interval{0x1B36, 0x1B3A},   Interval{0x1B3C, 0x1B3C},
    Interval{0x1B42, 0x1B42},   Interval{0x1B6B, 0x1B73},
    Interval{0x1DC0, 0x1DCA},   Interval{0x1DFE, 0x1DFF},
    Interval{0x200B, 0x200F},   Interval{0x202A, 0x202E},
    Interval{0x2060, 0x2063},   Interval{0x206A, 0x206F},
    Interval{0x20D0, 0x20EF},   Interval{0x302A, 0x302F},
    Interval{0x3099, 0x309A},   Interval{0xA806, 0xA806},
    Interval{0xA80B, 0xA80B},   Interval{0xA825, 0xA826},
    Interval{0xFB1E, 0xFB1E},   Interval{0xFE00, 0xFE0F},
    Interval{0xFE20, 0xFE23},   Interval{0xFEFF, 0xFEFF},
    Interval{0xFFF9, 0xFFFB},   Interval{0x10A01, 0x10A03},
    Interval{0x10A05, 0x10A06}, Interval{0x10A0C, 0x10A0F},
    Interval{0x10A38, 0x10A3A}, Interval{0x10A3F, 0x10A3F},
    Interval{0x1D167, 0x1D169}, Interval{0x1D173, 0x1D182},
    Interval{0x1D185, 0x1D18B}, Interval{0x1D1AA, 0x1D1AD},
    Interval{0x1D242, 0x1D244}, Interval{0xE0001, 0xE0001},
    Interval{0xE0020, 0xE007F}, Interval{0xE0100, 0xE01EF},
};

const std::array<Interval, 13> g_full_width_characters = {
    Interval{0x1100, 0x115f},   Interval{0x2329, 0x2329},
    Interval{0x232a, 0x232a},   Interval{0x2e80, 0x303e},
    Interval{0x3040, 0xa4cf},   Interval{0xac00, 0xd7a3},
    Interval{0xf900, 0xfaff},   Interval{0xfe10, 0xfe19},
    Interval{0xfe30, 0xfe6f},   Interval{0xff00, 0xff60},
    Interval{0xffe0, 0xffe6},   Interval{0x20000, 0x2fffd},
    Interval{0x30000, 0x3fffd},
};

// Find a codepoint inside a sorted list of Interval.
bool Bisearch(uint32_t ucs, const Interval* table, int max) {
  if (ucs < table[0].first || ucs > table[max].last) {  // NOLINT
    return false;
  }

  int min = 0;
  while (max >= min) {
    int mid = (min + max) / 2;
    if (ucs > table[mid].last) {  // NOLINT
      min = mid + 1;
    } else if (ucs < table[mid].first) {  // NOLINT
      max = mid - 1;
    } else {
      return true;
    }
  }

  return false;
}

bool IsCombining(uint32_t ucs) {
  return Bisearch(ucs, g_combining_characters.data(),
                  g_combining_characters.size() - 1);
}

bool IsFullWidth(uint32_t ucs) {
  if (ucs < 0x0300)  // Quick path: // NOLINT
    return false;

  return Bisearch(ucs, g_full_width_characters.data(),
                  g_full_width_characters.size() - 1);
}

bool IsControl(uint32_t ucs) {
  if (ucs == 0) {
    return true;
  }
  if (ucs < 32) {  // NOLINT
    return true;
  }
  if (ucs >= 0x7f && ucs < 0xa0) {  // NOLINT
    return true;
  }
  return false;
}

int codepoint_width(uint32_t ucs) {
  if (IsControl(ucs)) {
    return -1;
  }

  if (IsCombining(ucs)) {
    return 0;
  }

  if (IsFullWidth(ucs)) {
    return 2;
  }

  return 1;
}

// From UTF8 encoded string |input|, eat in between 1 and 4 byte representing
// one codepoint. Put the codepoint into |ucs|. Start at |start| and update
// |end| to represent the beginning of the next byte to eat for consecutive
// executions.
bool EatCodePoint(const std::string& input,
                  size_t start,
                  size_t* end,
                  uint32_t* ucs) {
  if (start >= input.size()) {
    *end = start + 1;
    return false;
  }
  uint8_t byte_1 = input[start];

  // 1 byte string.
  if ((byte_1 & 0b1000'0000) == 0b0000'0000) {  // NOLINT
    *ucs = byte_1 & 0b0111'1111;                // NOLINT
    *end = start + 1;
    return true;
  }

  // 2 byte string.
  if ((byte_1 & 0b1110'0000) == 0b1100'0000 &&  // NOLINT
      start + 1 < input.size()) {
    uint8_t byte_2 = input[start + 1];
    *ucs = 0;
    *ucs += byte_1 & 0b0001'1111;  // NOLINT
    *ucs <<= 6;                    // NOLINT
    *ucs += byte_2 & 0b0011'1111;  // NOLINT
    *end = start + 2;
    return true;
  }

  // 3 byte string.
  if ((byte_1 & 0b1111'0000) == 0b1110'0000 &&  // NOLINT
      start + 2 < input.size()) {
    uint8_t byte_2 = input[start + 1];
    uint8_t byte_3 = input[start + 2];
    *ucs = 0;
    *ucs += byte_1 & 0b0000'1111;  // NOLINT
    *ucs <<= 6;                    // NOLINT
    *ucs += byte_2 & 0b0011'1111;  // NOLINT
    *ucs <<= 6;                    // NOLINT
    *ucs += byte_3 & 0b0011'1111;  // NOLINT
    *end = start + 3;
    return true;
  }

  // 4 byte string.
  if ((byte_1 & 0b1111'1000) == 0b1111'0000 &&  // NOLINT
      start + 3 < input.size()) {
    uint8_t byte_2 = input[start + 1];
    uint8_t byte_3 = input[start + 2];
    uint8_t byte_4 = input[start + 3];
    *ucs = 0;
    *ucs += byte_1 & 0b0000'0111;  // NOLINT
    *ucs <<= 6;                    // NOLINT
    *ucs += byte_2 & 0b0011'1111;  // NOLINT
    *ucs <<= 6;                    // NOLINT
    *ucs += byte_3 & 0b0011'1111;  // NOLINT
    *ucs <<= 6;                    // NOLINT
    *ucs += byte_4 & 0b0011'1111;  // NOLINT
    *end = start + 4;
    return true;
  }

  *end = start + 1;
  return false;
}

}  // namespace

namespace ftxui {
int wchar_width(wchar_t ucs) {
  return codepoint_width(uint32_t(ucs));
}

int wstring_width(const std::wstring& text) {
  int width = 0;

  for (const wchar_t& it : text) {
    int w = wchar_width(it);
    if (w < 0) {
      return -1;
    }
    width += w;
  }
  return width;
}

int string_width(const std::string& input) {
  int width = 0;
  size_t start = 0;
  while (start < input.size()) {
    uint32_t codepoint = 0;
    if (!EatCodePoint(input, start, &start, &codepoint)) {
      continue;
    }

    if (IsControl(codepoint)) {
      continue;
    }

    if (IsCombining(codepoint)) {
      continue;
    }

    if (IsFullWidth(codepoint)) {
      width += 2;
      continue;
    }

    width += 1;
  }
  return width;
}

std::vector<std::string> Utf8ToGlyphs(const std::string& input) {
  std::vector<std::string> out;
  std::string current;
  out.reserve(input.size());
  size_t start = 0;
  size_t end = 0;
  while (start < input.size()) {
    uint32_t codepoint = 0;
    if (!EatCodePoint(input, start, &end, &codepoint)) {
      start = end;
      continue;
    }

    std::string append = input.substr(start, end - start);
    start = end;

    // Ignore control characters.
    if (IsControl(codepoint)) {
      continue;
    }

    // Combining characters are put with the previous glyph they are modifying.
    if (IsCombining(codepoint)) {
      if (!out.empty()) {
        out.back() += append;
      }
      continue;
    }

    // Fullwidth characters take two cells. The second is made of the empty
    // string to reserve the space the first is taking.
    if (IsFullWidth(codepoint)) {
      out.push_back(append);
      out.emplace_back("");
      continue;
    }

    // Normal characters:
    out.push_back(append);
  }
  return out;
}

int GlyphPosition(const std::string& input, size_t glyph_index, size_t start) {
  if (glyph_index <= 0) {
    return 0;
  }
  size_t end = 0;
  while (start < input.size()) {
    uint32_t codepoint = 0;
    bool eaten = EatCodePoint(input, start, &end, &codepoint);

    // Ignore invalid, control characters and combining characters.
    if (!eaten || IsControl(codepoint) || IsCombining(codepoint)) {
      start = end;
      continue;
    }

    // We eat the beginning of the next glyph. If we are eating the one
    // requested, return its start position immediately.
    if (glyph_index == 0) {
      return static_cast<int>(start);
    }

    // Otherwise, skip this glyph and iterate:
    glyph_index--;
    start = end;
  }
  return static_cast<int>(input.size());
}

std::vector<int> CellToGlyphIndex(const std::string& input) {
  int x = -1;
  std::vector<int> out;
  out.reserve(input.size());
  size_t start = 0;
  size_t end = 0;
  while (start < input.size()) {
    uint32_t codepoint = 0;
    bool eaten = EatCodePoint(input, start, &end, &codepoint);
    start = end;

    // Ignore invalid / control characters.
    if (!eaten || IsControl(codepoint)) {
      continue;
    }

    // Combining characters are put with the previous glyph they are modifying.
    if (IsCombining(codepoint)) {
      if (x == -1) {
        ++x;
        out.push_back(x);
      }
      continue;
    }

    // Fullwidth characters take two cells. The second is made of the empty
    // string to reserve the space the first is taking.
    if (IsFullWidth(codepoint)) {
      ++x;
      out.push_back(x);
      out.push_back(x);
      continue;
    }

    // Normal characters:
    ++x;
    out.push_back(x);
  }
  return out;
}

int GlyphCount(const std::string& input) {
  int size = 0;
  size_t start = 0;
  size_t end = 0;
  while (start < input.size()) {
    uint32_t codepoint = 0;
    bool eaten = EatCodePoint(input, start, &end, &codepoint);
    start = end;

    // Ignore invalid characters:
    if (!eaten || IsControl(codepoint)) {
      continue;
    }

    // Ignore combining characters, except when they don't have a preceding to
    // combine with.
    if (IsCombining(codepoint)) {
      if (size == 0) {
        size++;
      }
      continue;
    }

    size++;
  }
  return size;
}

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4996)  // codecvt_utf8_utf16 is deprecated
#endif

/// Convert a UTF8 std::string into a std::wstring.
std::string to_string(const std::wstring& s) {
  std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
  return converter.to_bytes(s);
}

/// Convert a std::wstring into a UTF8 std::string.
std::wstring to_wstring(const std::string& s) {
  std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
  return converter.from_bytes(s);
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif

}  // namespace ftxui

// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.
