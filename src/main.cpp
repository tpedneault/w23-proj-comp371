#include "engine/Engine.h"

/**
 * Entry point of the program.
 * @param argc number of arguments
 * @param argv program's arguments
 * @return error code
 */
int main(int argc, char **argv) {
  sc::Engine engine;
  engine.Start();
  return EXIT_SUCCESS;
}
