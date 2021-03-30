#pragma once
void CalcEarnings(Node* PtrNode);
void stateTree2HStar(Tree *Tree);
bool CheckDoneInside(Tree *Tree, PtrNodeType BackNode);
bool CheckNotDoneInside(Tree *Tree, PtrNodeType BackNotDoneNode);
void CaluDeadLockH(Tree *Tree);
