#include "ptbr_time.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

static const char* const HOURS[] = {
  "zero",
  "uma",
  "duas",
  "três",
  "quatro",
  "cinco",
  "seis",
  "sete",
  "oito",
  "nove",
  "dez",
  "onze",
  "doze"
};

static const char* const MINUTES[] = {
  "zero",
  "cinco",
  "dez",
  "quinze",
  "vinte",
  "vinte cinco"
};

static const char* STR_DIA   = "dia";
static const char* STR_NOITE = "noite";
static const char* STR_MEIO  = "meio";
static const char* STR_MEIA  = "meia";
static const char* STR_PONTO = "ponto";
static const char* STR_POUCO = "pouco";
static const char* STR_QUASE = "quase";
static const char* STR_PRAS  = "pras";
static const char* STR_PRA   = "pra";
static const char* STR_E     = "e";
static const char* STR_EM    = "em";

/**
 * Format Full Hour
 * ----------------
 *
 * 1.
 * 2. meio/meia
 * 3. dia/noite
 *
 * or
 *
 * 1. hora
 * 2. em
 * 3. ponto
 */
void
format_full_hour(int hour, char *line1, char *line2, char *line3)
{
  // meia noite
  if (hour == 0) {
    strcat(line2, STR_MEIA);
    strcat(line3, STR_NOITE);
  }

  // meio dia
  else if (hour == 12) {
    strcat(line2, STR_MEIO);
    strcat(line3, STR_DIA);
  }

  // hora em ponto
  else {
    if (hour > 12)
      hour -= 12;
    strcat(line1, HOURS[hour]);
    strcat(line2, STR_EM);
    strcat(line3, STR_PONTO);
  }
}

/**
  * First 30 minutes
  * ----------------
  *
  * 1. meio/meia
  * 2. dia/noite e
  * 3. minuto / 5
  *
  * or
  *
  * 1: hora
  * 2: e
  * 3: minuto / 5
  */
void
format_first_half(int hour, int minute, char *line1, char *line2, char *line3)
{
  // meia noite
  if (hour == 0) {
    strcat(line1, STR_MEIA);
    strcat(line2, STR_NOITE);
    strcat(line2, " ");
  }

  // meio dia
  else if (hour == 12) {
    strcat(line1, STR_MEIO);
    strcat(line2, STR_DIA);
    strcat(line2, " ");
  }

  // hora
  else {
    if (hour > 12)
      hour -= 12;
    strcat(line1, HOURS[hour]);
  }

  // minutes in multiple of five
  int multiple = (int)roundf(minute / 5.0f);

  // e minuto
  strcat(line2, STR_E);
  if (multiple == 0)
    strcat(line3, STR_POUCO);
  else if (multiple == 6)
    strcat(line3, STR_MEIA);
  else
    strcat(line3, MINUTES[multiple]);
}

/**
  * Last 30 minutes
  * ----------------
  *
  * 1. minuto / 5
  * 2. pra meio/meia
  * 3. dia/noite
  *
  * or
  *
  * 1: minuto / 5
  * 2: pra(s)
  * 3: hora
  */
void
format_last_half(int hour, int minute, char *line1, char *line2, char *line3)
{
  // minutes in multiple of five
  int multiple = 12 - (int)roundf(minute / 5.0f);

  // minuto
  if (multiple == 0) {
    strcat(line2, STR_QUASE);
  }
  else {
    // pra(s)
    if (hour == 0 || hour == 11 || hour == 23)
      strcat(line2, STR_PRA);
    else
      strcat(line2, STR_PRAS);

    strcat(line1, MINUTES[multiple]);
  }

  // meio dia
  if (hour == 11) {
    strcat(line2, " ");
    strcat(line2, STR_MEIO);
    strcat(line3, STR_DIA);
  }

  // meia noite
  else if (hour == 23) {
    strcat(line2, " ");
    strcat(line2, STR_MEIA);
    strcat(line3, STR_NOITE);
  }

  // hora
  else {
    hour += 1;
    if (hour > 12)
      hour -= 12;
    strcat(line3, HOURS[hour]);
  }
}

/**
 * Format Invalid
 * --------------
 *
 * Debug
 */
void
format_invalid(int hour, int minute, char *line1, char *line2, char *line3)
{
  /*char buff[10];*/
  /*sprintf(buff, "%02i:%02i", hour, minute);*/

  strcat(line1, "invalid");
  strcat(line2, "format");
  /*strcat(line3, buff);*/
}

void
fuzzy_time(int hour, int minute, char *line1, char *line2, char *line3)
{
  // clear lines
  strcpy(line1, "");
  strcpy(line2, "");
  strcpy(line3, "");

  // full hour
  if (minute == 0)
    format_full_hour(hour, line1, line2, line3);
  // first half
  else if (minute > 0 && minute < 33)
    format_first_half(hour, minute, line1, line2, line3);
  // last half
  else if (minute >= 33 && minute < 60)
    format_last_half(hour, minute, line1, line2, line3);
  else
    format_invalid(hour, minute, line1, line2, line3);
}
