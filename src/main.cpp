#include <argp.h>
#include <stdbool.h>
#include "mainSSD1306.h"
#include "mainMPU6050.h"

const char *argp_program_version = "programname programversion";
const char *argp_program_bug_address = "<your@email.address>";
static char doc[] = "Your program description.";
static char args_doc[] = "[FILENAME]...";
static struct argp_option options[] = {
  { "ssd1306", 's', 0, 0, "SSD1306 OLED Display"},
  { "mpu6050", 'm', 0, 0, "MPU6050 Device"},
  { 0 }
};

struct arguments {
  enum { NONE, MPU6050, SSD1306 } device;
};

static error_t parse_opt(int key, char *arg, struct argp_state *state) {
  struct arguments *arguments = (struct arguments*)state->input;

  switch (key)
  {
  case 's':
    arguments->device = arguments::SSD1306;
    break;
  case 'm':
    arguments->device = arguments::MPU6050;
    break;
  case ARGP_KEY_ARG:
    return 0;
  default:
    return ARGP_ERR_UNKNOWN;
  }

  return 0;
}

static struct argp argp = { options, parse_opt, args_doc, doc };

int main(int argc, char *argv[])
{
  struct arguments arguments;
  argp_parse(&argp, argc, argv, 0, 0, &arguments);

  if (arguments.device == arguments::NONE) {
    printf("No device specidied, try --help for more informations.\n");
    return 1;
  }

  if (arguments.device == arguments::SSD1306) {
    MainSSD1306::setup();
    while(1) {
      MainSSD1306::loop();
    }
  }

  if (arguments.device == arguments::MPU6050)
  {
    MainMPU6050::setup();
    while(1)
    {
      MainMPU6050::loop();
    }
  }

  return 0;
}
