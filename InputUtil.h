//
//  InputUtil.h
//  This class is a utility that reads input text for HMM, converts it
//  to a more compact binary file, and reads the binary file too
//  HMM
//
//  Created by Yudelson, Michael on 7/17/13.
//
//

#ifndef __HMM__InputUtil__
#define __HMM__InputUtil__

#include "utils.h"
#define bin_input_file_verstion 1

class InputUtil {
public:
    static bool readTxt(const char *fn, struct param * param); // read txt into param
    static bool readBin(const char *fn, struct param * param); // read bin into param
    static bool toBin(struct param * param, const char *fn);// writes data in param to bin file
private:
    static void writeString(FILE *f, string str);
    static string readString(FILE *f);
    static unsigned long writeMultiSkill(FILE *f, struct param * param);
    static unsigned long  readMultiSkill(FILE *f, struct param * param);
};
#endif /* defined(__HMM__InputUtil__) */