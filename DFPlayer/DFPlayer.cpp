#include "DFRobotDFPlayerMini.h"
#include "DFPlayer.h"

void INIT_DFPlayer(DFRobotDFPlayerMini &myDFPlayerF) {
  Serial1.begin(9600);
  if (!myDFPlayerF.begin(Serial1)) {
    Serial.println("DFPlayer did not begin");
    while (true);
  }
  myDFPlayerF.volume(10);
}
