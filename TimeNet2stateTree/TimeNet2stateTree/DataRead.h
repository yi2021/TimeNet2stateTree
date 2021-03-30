#pragma once
#define M0_path  "E:\\reinforce learning\\TimeNet2stateTree\\无死锁\\m0.txt"
#define Delay_path "E:\\reinforce learning\\TimeNet2stateTree\\无死锁\\delay.txt"
#define GoalPlace_path "E:\\reinforce learning\\TimeNet2stateTree\\无死锁\\GoalPlace.txt"
#define GoalMarking_path "E:\\reinforce learning\\TimeNet2stateTree\\无死锁\\GoalMarking.txt"

void DataRead(short place_num, short M0[], float Delay[], Tree *Tree);
void DataRead_v2(short place_num, short M0[], float Delay[], Tree *Tree);