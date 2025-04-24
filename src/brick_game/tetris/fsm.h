#ifndef FSM_H
#define FSM_H

#include "backend.h"

#ifdef __cplusplus
extern "C" {
#endif

void start_game();
void end_game();

void user_input_1(int input);
void user_input_2(int input);

void movement(all_parameters* get_all_parameters);

#ifdef __cplusplus
}
#endif

#endif  // FSM_H
