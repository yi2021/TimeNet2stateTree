#pragma once
#define M0_path  "E:\\reinforce learning\\TimeNet2stateTree\\������\\m0.txt"
#define Delay_path "E:\\reinforce learning\\TimeNet2stateTree\\������\\delay.txt"
#define GoalPlace_path "E:\\reinforce learning\\TimeNet2stateTree\\������\\GoalPlace.txt"
#define GoalMarking_path "E:\\reinforce learning\\TimeNet2stateTree\\������\\GoalMarking.txt"

void DataRead(short place_num, short M0[], float Delay[], Tree *Tree);
void DataRead_v2(short place_num, short M0[], float Delay[], Tree *Tree);