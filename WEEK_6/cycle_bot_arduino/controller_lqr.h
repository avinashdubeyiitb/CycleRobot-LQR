/*Global Variables*/
float reqthetadot = 0, reqtheta = 0, reqphi = 0, reqphidot = 0;
float errorthetadot = 0, errortheta = 0, errorphi = 0, errorphidot = 0;
double theta, phi;
double thetadot, phidot;
const float angle_offset = 00.5;
int dummy = 0;
float U = 0, U_new = 0,U_previous=0;
/******************/

void lqr(double roll,double angVelocity, double phi, double phidot)
{
  //Serial.println("in lqr");
  //Gain matrix optained from octave for sampling time of 7 ms
  float k[4] = {160.1  ,  19.191  ,  -0.79668  ,  2.3779};    // { distance, velocity, angle, angular velocity }
 // Serial.println(roll);
  //  Serial.println(mpu.roll_deg);
  //  Serial.print("omega= ");
  //  Serial.println(mpu.omega);
//     Serial.println(phi);
  // When traversing in the normal arena

  // k[1] += k[0];
  //k[0] = 0;
  reqtheta = 0;
  reqthetadot = 0;
  reqphi = 0;
  reqphidot = 0;


  errortheta = (roll - reqtheta) ;    //Error in the distance covered
  //  Serial.print(errortheta);
  //  Serial.print("\t");
  errorthetadot = (angVelocity - reqthetadot);           //Error in the velocity
  errorphi = (phi - reqphi) ;                         //Error in the tilt angle
  errorphidot = (phidot - reqphidot);                 //Error in angular velocity

  U = (-1 * (k[0] * errortheta) - (k[1] * errorthetadot) - (0 * errorphi) - (k[3] * errorphidot));
//  U=U-U_previous;
//  U_previous=U;
  U_new = constrain(U *255/6, -255, 255);
  
  //U_new = U * 255/12;
  //Serial.println(U);
 
Serial.println(U_new);
  //  if(U_new >= 0)
  //  {
  //    reaction.setDir(1);
  //    if(abs(U_new) >255)
  //    {
  //      reaction.setPWM(255);
  //    }
  //    reaction.setPWM(abs(U_new));
  //  }
  //  else
  //  {
  //    reaction.setDir(1);
  //    if(abs(U_new) >255)
  //    {
  //      reaction.setPWM(255);
  //    }
  //    reaction.setPWM(abs(U_new));
  //  }
  // Update the PWM  and direction
  reaction.setTheSpeed(U_new);

}
