#include <simplecpp>
#include <string>
#include <random>
#include "MovingObject.h"
#include "lasso.h"
#include "coin.h"
#include "bomb.h"
#include "score.h"
#include "instructions.h"

using namespace simplecpp;

void display(int score) {
      Score sc;
      string file_name = ".high_scores.txt";
      //Added a dot in front of the name to hide the file in Linux as a simple
      //(but somewhat effective) deterrent to cheating

      sc.display_high_scores(file_name);

      std::cout << endl;

      if (sc.size() < 10 || (sc.size() >= 10 && score > sc.get_score(sc.size() - 1))) {
            //If the high score file has less than 10 people in it, or if the last person on the
            //list is less than the score of the current user, append their score to the file.
            string user_name;
            std::cout << "Please enter your name: " << flush;
            cin >> user_name;
            std::cout << endl;

            sc.insert(user_name, score);
            sc.writeFile(file_name);

            sc.display_high_scores(file_name);
      }
}

main_program {

  initCanvas("Lasso", WINDOW_X, WINDOW_Y);
  instructions();

  int stepCount = 0;
  float stepTime = STEP_TIME;
  float runTime = -1; // sec; -ve means infinite
  float currTime = 0;

  // Draw lasso at start position
  double release_speed = INIT_RELEASE_SPEED; // m/s
  double release_angle_deg = INIT_RELEASE_ANGLE_DEG; // degrees
  double lasso_ax = 0;
  double lasso_ay = LASSO_G;
  bool paused = true;
  bool rtheta = true;
  Lasso lasso(release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);

  Line b1(0, PLAY_Y_HEIGHT, WINDOW_X, PLAY_Y_HEIGHT);
  b1.setColor(COLOR("blue"));
  Line b2(PLAY_X_START, 0, PLAY_X_START, WINDOW_Y);
  b2.setColor(COLOR("blue"));

  string msg("Cmd: _");
  Text charPressed(PLAY_X_START+50, PLAY_Y_HEIGHT+20, msg);
  char coinScoreStr[256];
  sprintf(coinScoreStr, "Coins: %d", lasso.getNumCoins());
  Text coinScore(PLAY_X_START+50, PLAY_Y_HEIGHT+50, coinScoreStr);

  paused = true; rtheta = true;
  double coin_speed = COIN_SPEED;
  double coin_angle_deg = COIN_ANGLE_DEG;
  double coin_ax = 0;
  double coin_ay = COIN_G;
  Coin coin(coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta);

  double bomb_speed = BOMB_SPEED;
  double bomb_angle_deg = BOMB_ANGLE_DEG;
  double bomb_ax = 0;
  double bomb_ay = BOMB_G;
  Bomb bomb(bomb_speed, bomb_angle_deg, bomb_ax, bomb_ay, paused, rtheta);

  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> udist3(1,3); // distribution in range [1, 3]
  //We want coins to be twice as likely to appear as bombs

  // After every COIN_GAP sec, make the coin jump
  double last_coin_jump_end = 0;

  // When t is pressed, throw lasso
  // If lasso within range, make coin stick
  // When y is pressed, yank lasso
  // When l is pressed, loop lasso
  // When q is pressed, quit

  bool gameContinue = true;
  bool bombRunning = false;
  bool coinRunning = true;

  while (gameContinue) {
    if((runTime > 0) && (currTime > runTime)) { break; }

    XEvent e;
    bool pendingEv = checkEvent(e);
    if(pendingEv) {
      char c = charFromEvent(e);
      msg[msg.length()-1] = c;
      charPressed.setMessage(msg);
      switch(c) {
            case 't':
                  lasso.unpause();
                  break;
            case 'y':
                  lasso.yank();
                  break;
            case 'l':
                  lasso.loopit();
                  if (coinRunning) {
                        lasso.check_for_coin(&coin);
                  }
                  if (bombRunning) {
                        lasso.check_for_bomb(&bomb);
                  }
                  if (!lasso.is_looped()) {
                        wait(STEP_TIME*5);
                  }
                  break;
            case '[':
                  if(lasso.isPaused()) { lasso.addAngle(-RELEASE_ANGLE_STEP_DEG);	}
                  break;
            case ']':
                  if(lasso.isPaused()) { lasso.addAngle(+RELEASE_ANGLE_STEP_DEG); }
                  break;
            case '-':
                  if(lasso.isPaused()) { lasso.addSpeed(-RELEASE_SPEED_STEP); }
                  break;
            case '=':
                  if(lasso.isPaused()) { lasso.addSpeed(+RELEASE_SPEED_STEP); }
                  break;
            case 'q':
                  gameContinue = false;
                  break;
            default:
                  break;
      }
    }


    lasso.nextStep(stepTime);

    if (coinRunning) {
      coin.nextStep(stepTime);
      if(coin.isPaused()) {
        if((currTime-last_coin_jump_end) >= COIN_GAP) {
              int num = udist3(rng);
        if (num % 3 == 0) {
              //Next up is a bomb
              coinRunning = false;
              bombRunning =  true;
        } else {
              //Next up is a coin
              coinRunning = true;
              bombRunning =  false;
        }
        last_coin_jump_end = currTime;
      }
	  coin.unpause();
        }
      }

      if(coin.getYPos() > PLAY_Y_HEIGHT) {
        coin.resetCoin();
        int num = udist3(rng);
        if (num % 3 == 0) {
              //Next up is a bomb
              coinRunning = false;
              bombRunning =  true;
        } else {
              //Next up is a coin
              coinRunning = true;
              bombRunning =  false;
        }
        last_coin_jump_end = currTime;
    }

    if (bombRunning) {
      bomb.nextStep(stepTime);
      if(bomb.isPaused()) {
        if((currTime-last_coin_jump_end) >= COIN_GAP) {
              int num = udist3(rng);
        if (num % 3 == 0) {
              //Next up is a bomb
              coinRunning = false;
              bombRunning =  true;
        } else {
              //Next up is a coin
              coinRunning = true;
              bombRunning =  false;
        }
        last_coin_jump_end = currTime;
	    bomb.unpause();
        }
      }

      if(bomb.getYPos() > PLAY_Y_HEIGHT) {
        bomb.resetBomb();
        int num = udist3(rng);
        if (num % 3 == 0) {
              //Next up is a bomb
              coinRunning = false;
              bombRunning =  true;
        } else {
              //Next up is a coin
              coinRunning = true;
              bombRunning =  false;
        }
        last_coin_jump_end = currTime;
      }
    }

    sprintf(coinScoreStr, "Coins: %d", lasso.getNumCoins());
    coinScore.setMessage(coinScoreStr);

    stepCount++;
    currTime += stepTime;
    wait(stepTime);
  } // End while

  std::cout << "Quitting game...\n" << endl;
  wait(0.5); //To make the output less abrupt
  std::cout << "Your score: " << lasso.getNumCoins() << endl;
  wait(1); //To make the output less abrupt
  std::cout << "\n\n";
  display(lasso.getNumCoins());

} // End main_program
