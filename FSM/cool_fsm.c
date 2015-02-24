 #define FSM            for(;;)
 #define STATE(x)       x##_s 
 #define NEXTSTATE(x)   goto x##_s

that you use this way:

 FSM {
    STATE(s1):
      ... do stuff ...
      NEXTSTATE(s2);

    STATE(s2):
      ... do stuff ...
      if (k<0) NEXTSTATE(s2); 
      /* fallthrough as the switch() cases */

    STATE(s3):
      ... final stuff ...
      break;  /* Exit from the FSM */
 }

