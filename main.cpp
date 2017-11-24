/*
Author: Jonathan Ek
Date: 2017-11-24
Description: The numerical version of the game bulls and cows
*/
#include<iostream>
#include<cstdlib>
#include<time.h>
#include<vector>
using namespace std;
int getNumberLength(int number) //Return the number of digits in a given number
{
  int retVal = 0;
  while(number > 0)
    {
    number /= 10;
    retVal ++;
    }
  return retVal;
}

int generateNumberWithUniqueDigits(int lengthOfNumber)
{
  int digitsArray[] = {1,2,3,4,5,6,7,8,9};
  std::vector<int> digitsVector(digitsArray,digitsArray + sizeof(digitsArray) / sizeof(int));
  int lengthOfVector = 9;
  srand(time(NULL));
  int currentNumber = 0;
  int multiplier = 1;
  int returnNumber = 0;
  while(lengthOfNumber > 0 )
    {
      std::vector<int>::iterator it = digitsVector.begin() + rand() % lengthOfVector;
      currentNumber = *it;
      returnNumber = returnNumber + currentNumber * multiplier;
      digitsVector.erase(it);
      lengthOfNumber --;
      lengthOfVector --;
      multiplier *= 10;
    }
  return returnNumber;
}
int checkIfNumberHasUniqueDigits(int number)
{
  int tempOne = number;
  int tempTwo;
  int currentNumber = 0;
  int numberToCompareCurrentNumberWith;
  while(tempOne > 0){
    currentNumber = tempOne % 10;
    tempTwo = tempOne /= 10;
    while(tempTwo > 0)
      {
	numberToCompareCurrentNumberWith = tempTwo % 10;
	if(numberToCompareCurrentNumberWith == currentNumber)
	  return 0;
	tempTwo /= 10;
      }
    tempOne /= 10;
      }
  return 1;
}
int numberOfBulls(int guess, int randomNumber)//A bull is a number in the random number and in the correct position
{
  int retVal = 0;
  while(guess > 0)
    {
      if((guess % 10) == (randomNumber % 10))
	retVal ++;
      guess /= 10;
      randomNumber /= 10;
    }
  return retVal;
}
int numberOfCows(int guess,int randomNumber) //A cow is a number that is in the random number but in the wrong position
{
  int currentNumber = 0;
  int tempOne = 0;
  int retVal = 0;
  int numberToCompareWith = 0;
  int numberOfDivisions = 0;
  int digitsPositionFromRight = 1;
  
  while(guess > 0)
    {
      currentNumber = guess % 10;
      tempOne = randomNumber;
      while(tempOne > 0)
	{
	  numberToCompareWith = tempOne % 10;
	  numberOfDivisions += 1;
	  if (numberOfDivisions != digitsPositionFromRight)
	    if(numberToCompareWith == currentNumber)
	      retVal += 1;
	  tempOne /= 10;
	}
      numberOfDivisions = 0;
      digitsPositionFromRight += 1;
      guess /= 10;
    }
  
       
  return retVal; 
}
using namespace std;
int main(){
  int expectedNumberLength = 4;
  int randomNumber = generateNumberWithUniqueDigits(expectedNumberLength);
  int guess = 0;
  int currentNumberOfBulls = 0;
  int currentNumberOfCows = 0;
  cout<<"I am thinking of a number. This number is 4 digits long and every digit inside it is unique."<<endl;
  cout<<"I want you to guess which number I am thinkning about"<<endl;
  cout<<"If your guess has a digit in a correct position then I will say that you have found a bull."<<endl;
  cout<<"If your guess has a digit that is in my number but in the wrong position I will say that you have found a cow"<<endl;
  
  cout<<"Guess a 4 digit number: "<<endl;
  cin>>guess;
 
  while(getNumberLength(guess) != expectedNumberLength || checkIfNumberHasUniqueDigits(guess) == 0)
    {
      cout<<"Your number has the wrong length or it does not have unique digits"<<endl;
      cin>>guess;
    }
  if(guess == randomNumber)
    {
      cout<<"Hmm, your first guess was correct"<<endl;
    }
  else
    {
      while(guess != randomNumber)
	{
	  currentNumberOfBulls = numberOfBulls(guess,randomNumber);
	  currentNumberOfCows = numberOfCows(guess,randomNumber);
	  cout<<"Number of Bulls == "<<currentNumberOfBulls<<" "<<"number of cows == "<<currentNumberOfCows<<endl;
	  cout<<"Make another guess"<<endl;
	  cin>>guess;
	  while(getNumberLength(guess) != expectedNumberLength || checkIfNumberHasUniqueDigits(guess) == 0)
	    {
	      cout<<"Your number has the wrong length or it does not have unique digits"<<endl;
	      cin>>guess;
	    }
	}
    }
  cout<<"You have won the game!"<<endl;
  return 0;
}

