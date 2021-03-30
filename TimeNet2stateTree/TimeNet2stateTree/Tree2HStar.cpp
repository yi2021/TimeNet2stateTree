#include<stdio.h>
#include <stdlib.h> 
#include<float.h>
#include"TreeNode.h"
#include"Tree2HStar.h"
#include <iostream>
using namespace std;
void stateTree2HStar(Tree *Tree)
{
	printf("begin Hstar\n");
	float H;
	bool over = 0;
	Node *PtrBackNode,*PtrFatherNode,*PtrpreNode=NULL,*PtrNotDoneNode,*PtrOldNode;
	PtrBackNode = Tree->PtrBackDoneHead;

	while (1)
	{
		Tree->Back_num++;
		if (PtrBackNode->markingID == 0)
		{
			if (PtrBackNode->TwinIsDone == 0)
			{
				PtrBackNode->TwinIsDone = 1;
				while (PtrBackNode->NumTwinBack)
				{
					PtrBackNode->NumTwinBack--;
					PtrBackNode->PtrSame[PtrBackNode->NumTwinBack]->hMin = PtrBackNode->hMin ;
					if (Tree->PtrBackOldHead == NULL)
					{
						Tree->PtrBackOldHead = PtrBackNode->PtrSame[PtrBackNode->NumTwinBack];
						Tree->PtrBackOldTail = PtrBackNode->PtrSame[PtrBackNode->NumTwinBack];
					}
					else
					{
						Tree->PtrBackOldTail->PtrBackOldNext = PtrBackNode->PtrSame[PtrBackNode->NumTwinBack];
						PtrBackNode->PtrSame[PtrBackNode->NumTwinBack]->PtrBackOldBefore = Tree->PtrBackOldTail;
						Tree->PtrBackOldTail = PtrBackNode->PtrSame[PtrBackNode->NumTwinBack];

					}
				}
			}
		}
		else
		{
			PtrFatherNode = PtrBackNode->PtrFathers[0];
			PtrFatherNode->NumSons_Back--;
			if (PtrFatherNode->NumSons_Back >= 0)
			{
				H = PtrBackNode->hMin + PtrBackNode->g - PtrFatherNode->g;
				if (H < PtrFatherNode->hMin)
				{
					PtrFatherNode->hMin = H;
				}
				if (PtrBackNode->TwinIsDone == 0)
				{
					PtrBackNode->TwinIsDone = 1;
					while (PtrBackNode->NumTwinBack)
					{
						PtrBackNode->NumTwinBack--;
						PtrBackNode->PtrSame[PtrBackNode->NumTwinBack]->hMin = PtrBackNode->hMin;
						if (Tree->PtrBackOldHead == NULL)
						{
							Tree->PtrBackOldHead = PtrBackNode->PtrSame[PtrBackNode->NumTwinBack];
							Tree->PtrBackOldTail = PtrBackNode->PtrSame[PtrBackNode->NumTwinBack];
						}
						else
						{
							Tree->PtrBackOldTail->PtrBackOldNext = PtrBackNode->PtrSame[PtrBackNode->NumTwinBack];
							PtrBackNode->PtrSame[PtrBackNode->NumTwinBack]->PtrBackOldBefore = Tree->PtrBackOldTail;
							Tree->PtrBackOldTail = PtrBackNode->PtrSame[PtrBackNode->NumTwinBack];

						}
					}
				}
				if (PtrFatherNode->NumSons_Back == 0)
				{
					if (CheckDoneInside(Tree, PtrFatherNode) == 0)
					{
						Tree->PtrBackDoneTail->PtrBackDoneNext = PtrFatherNode;
						Tree->PtrBackDoneTail = PtrFatherNode;
					}

					if (CheckNotDoneInside(Tree, PtrFatherNode) == 0 && PtrFatherNode->MultiSon == 1)
					{
						if (PtrFatherNode->PtrBackNotDoneBefore != NULL)
						{
							PtrFatherNode->PtrBackNotDoneBefore->PtrBackNotDoneNext = PtrFatherNode->PtrBackNotDoneNext;
						}
						else
						{
							Tree->PtrBackNotDoneHead = PtrFatherNode->PtrBackNotDoneNext;
						}
						if (PtrFatherNode->PtrBackNotDoneNext != NULL)
						{
							PtrFatherNode->PtrBackNotDoneNext->PtrBackNotDoneBefore = PtrFatherNode->PtrBackNotDoneBefore;
						}
						else
						{
							Tree->PtrBackNotDoneTail = PtrFatherNode->PtrBackNotDoneBefore;
						}
						PtrFatherNode->PtrBackNotDoneBefore = NULL;
						PtrFatherNode->PtrBackNotDoneNext = NULL;
					}
				}
				else
				{
					if (CheckNotDoneInside(Tree, PtrFatherNode))
					{
						if (Tree->PtrBackNotDoneHead == NULL)
						{
							Tree->PtrBackNotDoneHead = PtrFatherNode;
							Tree->PtrBackNotDoneTail = PtrFatherNode;
						}
						else
						{
							Tree->PtrBackNotDoneTail->PtrBackNotDoneNext = PtrFatherNode;
							PtrFatherNode->PtrBackNotDoneBefore = Tree->PtrBackNotDoneTail;
							Tree->PtrBackNotDoneTail = PtrFatherNode;
						}
					}
				}
			}
		}
		PtrBackNode = PtrBackNode->PtrBackDoneNext;
		if(PtrBackNode == NULL)
		{
			if (Tree->PtrBackOldHead == NULL)
			{
				if (Tree->PtrBackNotDoneHead == NULL)
				{
					break;
				}
				else
				{
					do
					{
						if (Tree->PtrBackNotDoneHead == NULL)
						{
							over = 1;
							break;
						}
						H = Tree->PtrBackNotDoneHead->hMin;
						PtrNotDoneNode = Tree->PtrBackNotDoneHead;
						do
						{
							if (H > PtrNotDoneNode->hMin)
							{
								H = PtrNotDoneNode->hMin;
								PtrpreNode = PtrNotDoneNode->PtrBackNotDoneBefore;
							}
							PtrNotDoneNode = PtrNotDoneNode->PtrBackNotDoneNext;

						} while (PtrNotDoneNode != NULL);
						if (PtrpreNode == NULL)
						{
							PtrBackNode = Tree->PtrBackNotDoneHead;
							Tree->PtrBackNotDoneHead = Tree->PtrBackNotDoneHead->PtrBackNotDoneNext;
						}
						else
						{
							PtrBackNode = PtrpreNode->PtrBackNotDoneNext;
							PtrpreNode->PtrBackNotDoneNext = PtrpreNode->PtrBackNotDoneNext->PtrBackNotDoneNext;
						}
						if (PtrBackNode->PtrBackNotDoneNext != NULL)
						{
							PtrBackNode->PtrBackNotDoneNext->PtrBackNotDoneBefore = PtrpreNode;
						}
						else
						{
							Tree->PtrBackNotDoneTail = PtrpreNode;
						}
						PtrBackNode->PtrBackNotDoneNext = NULL;
						PtrBackNode->PtrBackNotDoneBefore = NULL;
						PtrpreNode = NULL;

					} while (CheckDoneInside(Tree, PtrBackNode));
					if (over == 1)
					{
						break;
					}
					Tree->PtrBackDoneTail->PtrBackDoneNext = PtrBackNode;
					Tree->PtrBackDoneTail = PtrBackNode;
			
				}
			}
			else
			{	
				do
				{
					if (Tree->PtrBackOldHead == NULL)
					{
						over = 1;
						break;
					}
					H = Tree->PtrBackOldHead->hMin;
					PtrOldNode = Tree->PtrBackOldHead;
					do
					{
						if (H > PtrOldNode->hMin)
						{
							H = PtrOldNode->hMin;
							PtrpreNode = PtrOldNode->PtrBackOldBefore;
						}
						PtrOldNode = PtrOldNode->PtrBackOldNext;

					} while (PtrOldNode != NULL);
					if (PtrpreNode == NULL)
					{
						PtrBackNode = Tree->PtrBackOldHead;
						Tree->PtrBackOldHead = Tree->PtrBackOldHead->PtrBackOldNext;
					}
					else
					{
						PtrBackNode = PtrpreNode->PtrBackOldNext;
						PtrpreNode->PtrBackOldNext = PtrpreNode->PtrBackOldNext->PtrBackOldNext;
					}
					if (PtrBackNode->PtrBackOldNext != NULL)
					{
						PtrBackNode->PtrBackOldNext->PtrBackOldBefore = PtrpreNode;
					}
					else
					{
						Tree->PtrBackOldTail = PtrpreNode;
					}
					PtrBackNode->PtrBackOldNext = NULL;
					PtrBackNode->PtrBackOldBefore = NULL;
					PtrpreNode = NULL;

				} while (CheckDoneInside(Tree, PtrBackNode));

				if (over == 1)
				{
					over = 0;
					if (Tree->PtrBackNotDoneHead == NULL)
					{
						break;
					}
					else
					{
						do
						{
							if (Tree->PtrBackNotDoneHead == NULL)
							{
								over = 1;
								break;
							}
							H = Tree->PtrBackNotDoneHead->hMin;
							PtrNotDoneNode = Tree->PtrBackNotDoneHead;
							do
							{
								if (H > PtrNotDoneNode->hMin)
								{
									H = PtrNotDoneNode->hMin;
									PtrpreNode = PtrNotDoneNode->PtrBackNotDoneBefore;
								}
								PtrNotDoneNode = PtrNotDoneNode->PtrBackNotDoneNext;

							} while (PtrNotDoneNode != NULL);
							if (PtrpreNode == NULL)
							{
								PtrBackNode = Tree->PtrBackNotDoneHead;
								Tree->PtrBackNotDoneHead = Tree->PtrBackNotDoneHead->PtrBackNotDoneNext;
							}
							else
							{
								PtrBackNode = PtrpreNode->PtrBackNotDoneNext;
								PtrpreNode->PtrBackNotDoneNext = PtrpreNode->PtrBackNotDoneNext->PtrBackNotDoneNext;
							}
							if (PtrBackNode->PtrBackNotDoneNext != NULL)
							{
								PtrBackNode->PtrBackNotDoneNext->PtrBackNotDoneBefore = PtrpreNode;
							}
							else
							{
								Tree->PtrBackNotDoneTail = PtrpreNode;
							}
							PtrBackNode->PtrBackNotDoneNext = NULL;
							PtrBackNode->PtrBackNotDoneBefore = NULL;
							PtrpreNode = NULL;

						} while (CheckDoneInside(Tree, PtrBackNode));
						if (over == 1)
						{
							break;
						}
						Tree->PtrBackDoneTail->PtrBackDoneNext = PtrBackNode;
						Tree->PtrBackDoneTail = PtrBackNode;

					}
				}
				else
				{
					Tree->PtrBackDoneTail->PtrBackDoneNext = PtrBackNode;
					Tree->PtrBackDoneTail = PtrBackNode;
				}
			}
		}
	}

	if (Tree->PtrDeadlockHead != NULL)
	{
		CaluDeadLockH(Tree);
	}
	PtrBackNode = Tree->PtrBackDoneHead;
	while (PtrBackNode != nullptr)
	{
		if (PtrBackNode->Earnings == nullptr)
		{
			CalcEarnings(PtrBackNode);
			PtrBackNode = PtrBackNode->PtrBackDoneNext;
		}
		else
			PtrBackNode = PtrBackNode->PtrBackDoneNext;

	}
	printf("Back_num:%d\n", Tree->Back_num);

	printf("over Hstar\n");
}


bool CheckDoneInside(Tree *Tree,PtrNodeType BackNode)
{
	PtrNodeType PtrBack;
	PtrBack = Tree->PtrBackDoneHead;
	while (PtrBack != NULL)
	{
		if (BackNode->markingID == PtrBack->markingID)
		{
			return 1;
		}
		PtrBack = PtrBack->PtrBackDoneNext;
	} 
	return 0;
}

bool CheckNotDoneInside(Tree *Tree, PtrNodeType BackNotDoneNode)
{
	PtrNodeType PtrBack;
	PtrBack = Tree->PtrBackNotDoneHead;
	while (PtrBack != NULL)
	{
		if (BackNotDoneNode->markingID == PtrBack->markingID)
		{
			return 0;
		}
		PtrBack = PtrBack->PtrBackNotDoneNext;
	}
	return 1;
}

bool CheckDeadLockInside(Tree *Tree, PtrNodeType DeadLock)
{
	PtrNodeType PtrDeadNode;
	PtrDeadNode = Tree->PtrDeadlockHead;
	while (PtrDeadNode != NULL)
	{
		if (DeadLock->markingID == PtrDeadNode->markingID)
		{
			return 0;
		}
		PtrDeadNode = PtrDeadNode->DeadlockNext;
	}
	return 1;
}

void CaluDeadLockH(Tree *Tree)
{
	PtrNodeType PtrDeadLock;
	PtrDeadLock = Tree->PtrDeadlockHead;
	float h;
	do
	{
		h = FLT_MAX;
		for (short i = 0; i < PtrDeadLock->NumFathers; ++i)
		{
			if (PtrDeadLock->PtrFathers[i]->isDeadlock != 1)
			{
				if (PtrDeadLock->PtrFathers[i]->hMin == FLT_MAX)
				{
					Tree->PtrDeadlockTail->DeadlockNext = PtrDeadLock;
					Tree->PtrDeadlockTail = PtrDeadLock;
					PtrDeadLock->isDeadlock = 1;
				}
				else
				{

					for (short j = 0; j < PtrDeadLock->PtrFathers[i]->NumSons; j++)
					{
						if (PtrDeadLock->PtrFathers[i]->Ptrsons[j]->isDeadlock == 0 && PtrDeadLock->PtrFathers[i]->Ptrsons[j]->hMin < h)
						{
							h = PtrDeadLock->PtrFathers[i]->Ptrsons[j]->hMin;
						}
					}
				}
			}
		}
		PtrDeadLock->hMin = (h * 1.5);
		PtrDeadLock = PtrDeadLock->DeadlockNext;
	} while (PtrDeadLock !=NULL);
}

void CalcEarnings(Node* PtrNode)
{
	if (PtrNode->hMin == 0)
		return;
	else
	{
		float Q;
		PtrNode->Earnings = new float[PtrNode->NumSons];
		for (int i = 0; i < PtrNode->NumSons; i++)
		{
			Q = -(PtrNode->Ptrsons[i]->g - PtrNode->g) - PtrNode->Ptrsons[i]->hMin;
			PtrNode->Earnings[i] = Q;
			//cout << PtrNode->Ptrsons[i]->hMin << "Q=" << Q << " " << "t" << *(PtrNode->Ptrsons[i]->PtrFiredTransitions) << "   " << endl;;
			//PtrNode->Earnings.insert(pair<short, float>(i, Q));
			/*if (PtrNode->PtrEarning == nullptr)
			{
				PtrNode->PtrEarning = new Earning(*(PtrNode->Ptrsons[i]->PtrFiredTransitions), Q);
				PtrNode->PtrEanringHead = PtrNode->PtrEarning;
			}
			else
				PtrNode->PtrEarning->insert(*(PtrNode->Ptrsons[i]->PtrFiredTransitions), Q);*/
		}
	}
	//cout << endl;
}