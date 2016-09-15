﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
using System.IO;
using System.Drawing.Imaging;
using League_Autoplay.High_Performance_Timer;
using Debug = System.Diagnostics.Debug;

namespace League_Autoplay.AutoQueue
{
    public class AutoQueueManager
    {

        Bitmap acceptMatchButton, dontSendButton, randomChampButton, reconnectButton, playAgainButton, lockInButton;
        Position acceptMatchButtonPosition, dontSendButtonPosition, randomChampButtonPosition, reconnectButtonPosition, playAgainButtonPosition, lockInButtonPosition;
        Stopwatch acceptMatchClickStopwatch, dontSendClickStopwatch, randomChampClickStopwatch, reconnectButtonClickStopwatch, playAgainButtonStopwatch, lockInButtonStopwatch;
        Stopwatch errorCheckScanStopwatch;
        Stopwatch sleepStopwatch;

        Stopwatch printStatus;

        int sleepCount = 0;
        double sleepAwakeTime = 3;

        bool sleeping = false;

        public AutoQueueManager()
        {
            string dir = Path.GetDirectoryName(System.Windows.Forms.Application.ExecutablePath);
            acceptMatchButton = new Bitmap(Image.FromFile(Path.Combine(dir, "AnalysisImages\\Resources\\Auto Queue Images\\Accept Match Button.png")));
            dontSendButton = new Bitmap(Image.FromFile(Path.Combine(dir, "AnalysisImages\\Resources\\Auto Queue Images\\Dont Send Button.png")));
            randomChampButton = new Bitmap(Image.FromFile(Path.Combine(dir, "AnalysisImages\\Resources\\Auto Queue Images\\Random Champ Button.png")));
            reconnectButton = new Bitmap(Image.FromFile(Path.Combine(dir, "AnalysisImages\\Resources\\Auto Queue Images\\Reconnect Button.png")));
            playAgainButton = new Bitmap(Image.FromFile(Path.Combine(dir, "AnalysisImages\\Resources\\Auto Queue Images\\Play Again Button.png")));
            lockInButton = new Bitmap(Image.FromFile(Path.Combine(dir, "AnalysisImages\\Resources\\Auto Queue Images\\Lock In Button.png")));

            acceptMatchClickStopwatch = new Stopwatch();
            dontSendClickStopwatch = new Stopwatch();
            randomChampClickStopwatch = new Stopwatch();
            reconnectButtonClickStopwatch = new Stopwatch();
            playAgainButtonStopwatch = new Stopwatch();
            lockInButtonStopwatch = new Stopwatch();
            errorCheckScanStopwatch = new Stopwatch();
            sleepStopwatch = new Stopwatch();
            sleeping = false;

            printStatus = new Stopwatch();

            sleepCount = 0;
        }

        //public void reset()
        //{
        //
        //}

        public void runErrorCheck(Bitmap screen)
        {
            if (errorCheckScanStopwatch.DurationInSeconds() <= 5.0) return;
            errorCheckScanStopwatch.Reset();

            if (dontSendClickStopwatch.DurationInMilliseconds() >= 500 || VisualCortex.IsTest)
            {
                dontSendButtonPosition = AutoQueueDetection.findImageInScreen(screen, dontSendButton, 465, 535, 10, 10, 0.95);
                if (dontSendButtonPosition.x != -1)
                {
                    Console.WriteLine("\tFound dont send button");
                    if (!VisualCortex.IsTest)
                    {
                        MotorCortex.clickMouseAt(dontSendButtonPosition.x + 10, dontSendButtonPosition.y + 10);
                        moveMouseToWithDelay(0, 0, 200);
                    }
                    dontSendClickStopwatch.Reset();
                    return;
                }
            }
        }

        public void nextSleepTime()
        {
            if (sleepCount == 0)
            {
                sleepCount++;
                sleeping = true;
                sleepAwakeTime = 1.0;
            } else if (sleepCount == 1)
            {
                sleepCount++;
                sleeping = false;
                sleepAwakeTime = 3.0;
            } else if (sleepCount == 2)
            {
                sleepCount++;
                sleeping = true;
                sleepAwakeTime = 1.0;
            }
            else if (sleepCount == 3)
            {
                sleepCount++;
                sleeping = false;
                sleepAwakeTime = 3.0;
            }
            else if (sleepCount == 4)
            {
                sleepCount++;
                sleeping = true;
                sleepAwakeTime = 1.0;
            }
            else if (sleepCount == 5)
            {
                sleepCount++;
                sleeping = false;
                sleepAwakeTime = 3.0;
            }
            else if (sleepCount == 6)
            {
                sleepCount++;
                sleeping = true;
                sleepAwakeTime = 8.0;
            }
            else if (sleepCount == 7)
            {
                sleepCount = 0;
                sleeping = false;
                sleepAwakeTime = 3.0;
            }
        }

        public void runSleepLogic()
        {
            //Handle sleeping
            if (sleeping)
            {
                if (sleepStopwatch.DurationInHours() >= sleepAwakeTime)
                {  //Sleep for 30 minutes then play
                    //sleeping = false;
                    nextSleepTime();
                    sleepStopwatch.Reset();
                }
            }
            else
            {
                if (sleepStopwatch.DurationInHours() >= sleepAwakeTime)
                {  //Play for 2 hours then sleep
                    //sleeping = true;
                    nextSleepTime();
                    sleepStopwatch.Reset();
                }
            }


            if (printStatus.DurationInMinutes() >= 1.0)
            {
                printStatus.Reset();
                String output = string.Format("{0:HH:mm:ss tt}", DateTime.Now) + "Auto Queue Status: " + (sleeping ? "Sleeping" : "Awake");
                if (sleeping) output += " with " + (30 - sleepStopwatch.DurationInMinutes()) + " minutes left";
                if (!sleeping) output += " with " + (120 - sleepStopwatch.DurationInMinutes()) + " minutes left";
                Console.WriteLine(output);
            }
        }

        public void runAutoQueue(Bitmap screen)
        {
            //Loop through pixels on the screen and look for any of those four buttons.
            if (lockInButtonStopwatch.DurationInMilliseconds() >= 5000 || VisualCortex.IsTest)
            {
                //Console.WriteLine("Scanning for lock in button");
                lockInButtonPosition = AutoQueueDetection.findImageInScreen(screen, lockInButton, 660, 441, 10, 10, 0.95);
                //acceptMatchButtonPosition = AutoQueueDetection.findImageInScreen(screen, acceptMatchButton, 0, 0, 1024, 768, 0.5);
                if (lockInButtonPosition.x != -1)
                {
                    lockInButtonStopwatch.Reset();
                    Console.WriteLine("\tFound lock in button at " + lockInButtonPosition.x + ", " + lockInButtonPosition.y);
                    if (!VisualCortex.IsTest)
                    {
                        MotorCortex.clickMouseAt(lockInButtonPosition.x + 10, lockInButtonPosition.y + 10);
                        

                        int x = lockInButtonPosition.x - 419;
                        int y = lockInButtonPosition.y + 191;

                        moveMouseToWithDelay(x, y, 200);

                        //Click Enter
                        Task.Delay(400).ContinueWith(_ =>
                        {
                            MotorCortex.clickMouseAt(x, y);
                        });
                        Task.Delay(600).ContinueWith(_ =>
                        {
                            MotorCortex.typeText("T");
                        });
                        Task.Delay(800).ContinueWith(_ =>
                        {
                            MotorCortex.typeText("o");
                        });
                        Task.Delay(1000).ContinueWith(_ =>
                        {
                            MotorCortex.typeText("p");
                        });
                        Task.Delay(1200).ContinueWith(_ =>
                        {
                            MotorCortex.tapEnterKey();
                        });
                        
                    }

                    if (!VisualCortex.IsTest) return;
                }
            }
            if (acceptMatchClickStopwatch.DurationInMilliseconds() >= 500 || VisualCortex.IsTest)
            {
                acceptMatchButtonPosition = AutoQueueDetection.findImageInScreen(screen, acceptMatchButton, 366, 393, 10, 10, 0.70);
                if (VisualCortex.IsTest) Console.WriteLine("Searching for accept button");
                //acceptMatchButtonPosition = AutoQueueDetection.findImageInScreen(screen, acceptMatchButton, 0, 0, 1024, 768, 0.5);
                if (acceptMatchButtonPosition.x != -1)
                {
                    acceptMatchClickStopwatch.Reset();
                    Console.WriteLine("\tFound accept match button at " + acceptMatchButtonPosition.x + ", " + acceptMatchButtonPosition.y);
                    if (!VisualCortex.IsTest)
                    {
                        MotorCortex.clickMouseAt(acceptMatchButtonPosition.x + 10, acceptMatchButtonPosition.y + 10);
                        moveMouseToWithDelay(0, 0, 200);
                    }
                    if (!VisualCortex.IsTest) return;
                }
            }
            if (randomChampClickStopwatch.DurationInMilliseconds() >= 2000 || VisualCortex.IsTest)
            {
                randomChampButtonPosition = AutoQueueDetection.findImageInScreen(screen, randomChampButton, 235, 186, 10, 10, 0.95);
                if (randomChampButtonPosition.x != -1)
                {

                    randomChampClickStopwatch.Reset();
                    Console.WriteLine("\tFound random champ button");
                    if (!VisualCortex.IsTest)
                    {

                        MotorCortex.clickMouseAt(randomChampButtonPosition.x + 10, randomChampButtonPosition.y + 10);
                        moveMouseToWithDelay(0, 0, 200);
                        /*
                        //Click Enter
                        Task.Delay(200).ContinueWith(_ =>
                        {
                            MotorCortex.typeText("{ENTER}");
                        });
                        Task.Delay(400).ContinueWith(_ =>
                        {
                            MotorCortex.typeText("T", true);
                        });
                        Task.Delay(600).ContinueWith(_ =>
                        {
                            MotorCortex.typeText("o", true);
                        });
                        Task.Delay(800).ContinueWith(_ =>
                        {
                            MotorCortex.typeText("p", true);
                        });
                        Task.Delay(1000).ContinueWith(_ =>
                        {
                            MotorCortex.typeText("{ENTER}");
                        });
                        */
                    }
                    if (!VisualCortex.IsTest) return;
                }
            }
            if (reconnectButtonClickStopwatch.DurationInMilliseconds() >= 500 || VisualCortex.IsTest)
            {
                reconnectButtonPosition = AutoQueueDetection.findImageInScreen(screen, reconnectButton, 438, 394, 10, 10, 0.95);
                if (reconnectButtonPosition.x != -1)
                {
                    reconnectButtonClickStopwatch.Reset();
                    Console.WriteLine("\tFound reconnect button");
                    if (!VisualCortex.IsTest)
                    {
                        MotorCortex.clickMouseAt(reconnectButtonPosition.x + 10, reconnectButtonPosition.y + 10);
                        moveMouseToWithDelay(0, 0, 200);
                    }
                    if (!VisualCortex.IsTest) return;
                }
            }
            if ((playAgainButtonStopwatch.DurationInMilliseconds() >= 5000 && sleeping == false) || VisualCortex.IsTest)
            {
                playAgainButtonPosition = AutoQueueDetection.findImageInScreen(screen, playAgainButton, 776, 616, 10, 10, 0.95);
                if (playAgainButtonPosition.x != -1)
                {
                    playAgainButtonStopwatch.Reset();
                    Console.WriteLine("\tFound play again button");
                    if (!VisualCortex.IsTest)
                    {
                        MotorCortex.clickMouseAt(playAgainButtonPosition.x + 10, playAgainButtonPosition.y + 10);
                        moveMouseToWithDelay(0, 0, 500);
                    }
                    if (!VisualCortex.IsTest) return;
                }
            }
        }
        public void enteredLeagueOfLegends()
        {
            MotorCortex.releaseControlKey();
            MotorCortex.releaseShiftKey();
            MotorCortex.pressTabKey();
        }
        public void exitedLeagueOfLegends()
        {
            MotorCortex.moveMouseTo(0, 0, 1);
            MotorCortex.releaseControlKey();
            MotorCortex.releaseShiftKey();
            MotorCortex.pressTabKey();
        }
        public void clickMouseAtWithDelay(int x, int y, int delay)
        {
            Task.Delay(delay).ContinueWith(_ =>
            {
                MotorCortex.clickMouseAt(x, y, 1);
            });
        }
        public void moveMouseToWithDelay(int x, int y, int delay)
        {
            Task.Delay(delay).ContinueWith(_ =>
            {
                MotorCortex.moveMouseTo(x, y, 1);
            });
        }
    }
}
