========================================================================================
Files, Pointers and Strings: C4 28/10/21

╔════════════╗
║Preparation:║
╚════════════╝

1) The * operator is used in front of a name of a pointer to tell the compiler to read the value at that memory address.  The & operator is used in front of a name of a variable to tell the compiler to read the starting memory address of that variable.

2)
┌────────────────────────────────────────────────┐
void arredit(int *array, int len){
    for(int i; i < len; i++){
        array[i] += 1;
    }
}

void main(){
    int arr[] = {1, 2, 3, 4, 5, \0};
    for(int i; i < 5; i++){
        printf("%d ,", arr[i]);
    }
    arredit(&arr, 5);
    for(int i; i < 5; i++){
        printf("%d ,", arr[i]);
    }
}
└────────────────────────────────────────────────┘

3) (https://en.cppreference.com/w/c/io)

FILE is an object type used to specify the type of pointer you are defining (which you must do as you need to point to the memory location of that file).

FILE *filepointer;

fopen() is a function that takes in a pointer to the location of the file to be modified, and also takes in an input to decide the mode in which the file will be manipulated, opening the file.

r  = read an existing file
w  = writing (overwrite)
a  = append the file
r+ = read and write to an existing file
w+ = read and write to a new file
a+ = read and append a file

FILE *location = "path/to/directory";
FILE filepointer = fopen(location, "w+");

fclose() is a function that takes in a a pointer to the location of the file to be modified, closing the file.

fclose(filepointer);

fgetc() is a function that returns the next character of the file read, taking the file pointer as an input.  This can be combined with feof() which also takes the file pointer as an input, to tell the program when the end of the file has been reached.

char a;
while(!feof(filepointer)){
    a = fgetc(filepointer);
    printf("%c", a);
}

4)
┌────────────────────────────────────────────────┐
#include <stdio.h>

void main(){
    char a;
    FILE *file = fopen("test.txt", "r");
    if(!file){
        printf("error reading file");
    }
    while(!feof(file)){
        a = fgetc(file);
        printf("%c", a);
        // Prints text.txt "This is a file".
    }
    fclose(file);
}
└────────────────────────────────────────────────┘

5) isalpha() and toupper() are both functions in the ctype.h header used to manipulate characters.  isalpha() returns a logic value, testing whether the input is alphabetic, toupper() returns the upper case value of the character input.

6) "A" is represented by 65

7) The Caesar cipher is a very simple form of encryption that essentially shifts the alphabetic positions of each character over by a fixed value such that the spacing between each character stays the same, but the position of each character has an offset.

8) The modulo operation is performed by the % operand.

========================================================================================

╔════════════════╗
║Laboratory Work:║
╚════════════════╝

3.1 ["Reading from Files"]

┌──────────────────────────────────────────────────────────────────────────────────────┐
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#define TERMINALWIDTH 100

char *filelocation = "3.1.txt";

void calculateHistogram(char *filename, int *alphabetarray);
void printValue(const int *alphanum);
void plot(const int *alphanum, int width);

void main(){
    char a;
    int alphabet[26];
    for(int i = 0; i < 26; i++){
        alphabet[i] = 0;
    }
    FILE *file = fopen(filelocation, "r");
    if(!file){
        printf("error reading file");
    }
    while(!feof(file)){
        a = fgetc(file);
        if(isalpha(a)){
            printf("%c", toupper(a));
        }
        else{
            printf("_");
        }
    }
    fclose(file);
    printf("\n");
    calculateHistogram(filelocation, alphabet);
    printf("\n");
    printValue(alphabet);
    printf("\n");
    plot(alphabet, TERMINALWIDTH);
}

void calculateHistogram(char *fn, int *arr){
    char a;
    FILE *file = fopen(fn, "r");
    if(!file){
        printf("error reading file");
    }
    while(!feof(file)){
        a = fgetc(file);
        if(isalpha(a)){
            a = toupper(a);
            // printf("\n");
            //printf("%d, ", a);
            arr[a-65] += 1;
            //printf("%d, ", arr[a-65]);
        }
        else{}
    }
    fclose(file);
}

void printValue(const int *arr){
    for(int i = 0; i < 26; i++){
        printf("%d\n", arr[i]);
    }
}

void plot(const int *arr, int width){
    int maxnum = 0;
    float scale = 0;
    for(int i = 0; i < 26; i++){
        if(arr[i] > maxnum){
            maxnum = arr[i];
        }
        else{}
    }
    scale = ceil((float)width/maxnum);
    for(int i = 0; i < 26; i++){
        for(int j = 0; j < floor(arr[i]*scale); j++){
            printf("█");
        }
        printf("\n");
    }
}
└──────────────────────────────────────────────────────────────────────────────────────┘

["INPUT TEXT:"]

6.522 There is indeed the inexpressible. This shows itself; it is the
mystical.

6.53 The right method of philosophy would be this. To say nothing
except what can be said, i.e. the propositions of natural science,
i.e. something that has nothing to do with philosophy: and then
always, when someone else wished to say something metaphys-
ical, to demonstrate to him that he had given no meaning to
certain signs in his propositions. This method would be un-
satisfying to the other—he would not have the feeling that we
were teaching him philosophy—but it would be the only strictly
correct method.

6.54 My propositions are elucidatory in this way: he who understands
me finally recognizes them as senseless, when he has climbed out
through them, on them, over them. (He must so to speak throw
away the ladder, after he has climbed up on it.)
He must surmount these propositions; then he sees the world
rightly.

7 Whereof one cannot speak, thereof one must be silent.

https://www.gutenberg.org/files/5740/5740-pdf.pdf
Tractatus Logico-Philosophicus
Ludwig Wittgenstein.

["TERMINAL OUTPUT:"]

______THERE_IS_INDEED_THE_INEXPRESSIBLE__THIS_SHOWS_ITSELF__IT_IS_THE_MYSTICAL________THE_RIGHT_METHOD_OF_PHILOSOPHY_WOULD_BE_THIS__TO_SAY_NOTHING_EXCEPT_WHAT_CAN_BE_SAID__I_E__THE_PROPOSITIONS_OF_NATURAL_SCIENCE__I_E__SOMETHING_THAT_HAS_NOTHING_TO_DO_WITH_PHILOSOPHY__AND_THEN_ALWAYS__WHEN_SOMEONE_ELSE_WISHED_TO_SAY_SOMETHING_METAPHYS__ICAL__TO_DEMONSTRATE_TO_HIM_THAT_HE_HAD_GIVEN_NO_MEANING_TO_CERTAIN_SIGNS_IN_HIS_PROPOSITIONS__THIS_METHOD_WOULD_BE_UN__SATISFYING_TO_THE_OTHER___HE_WOULD_NOT_HAVE_THE_FEELING_THAT_WE_WERE_TEACHING_HIM_PHILOSOPHY___BUT_IT_WOULD_BE_THE_ONLY_STRICTLY_CORRECT_METHOD________MY_PROPOSITIONS_ARE_ELUCIDATORY_IN_THIS_WAY__HE_WHO_UNDERSTANDS_ME_FINALLY_RECOGNIZES_THEM_AS_SENSELESS__WHEN_HE_HAS_CLIMBED_OUT_THROUGH_THEM__ON_THEM__OVER_THEM___HE_MUST_SO_TO_SPEAK_THROW_AWAY_THE_LADDER__AFTER_HE_HAS_CLIMBED_UP_ON_IT___HE_MUST_SURMOUNT_THESE_PROPOSITIONS__THEN_HE_SEES_THE_WORLD_RIGHTLY_____WHEREOF_ONE_CANNOT_SPEAK__THEREOF_ONE_MUST_BE_SILENT___HTTPS___WWW_GUTENBERG_ORG_FILES___________PDF_PDF_TRACTATUS_LOGICO_PHILOSOPHICUS_LUDWIG_WITTGENSTEIN___

41
10
19
26
101
12
20
73
65
0
2
31
24
52
71
25
0
32
69
91
21
3
24
2
17
1

█████████████████████████████████████████
██████████
███████████████████
██████████████████████████
█████████████████████████████████████████████████████████████████████████████████████████████████████
████████████
████████████████████
█████████████████████████████████████████████████████████████████████████
█████████████████████████████████████████████████████████████████

██
███████████████████████████████
████████████████████████
████████████████████████████████████████████████████
███████████████████████████████████████████████████████████████████████
█████████████████████████

████████████████████████████████
█████████████████████████████████████████████████████████████████████
███████████████████████████████████████████████████████████████████████████████████████████
█████████████████████
███
████████████████████████
██
█████████████████
█

// This text editor is not as wide as my terminal

3.2 ["Manipulating Strings"]

┌──────────────────────────────────────────────────────────────────────────────────────┐
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#define OFFSET 20

char *filelocation = "3.1.txt";
char *encrypted = "3.2enc.txt";
char *decrypted = "3.2dec.txt";

void encipher(const char *p, char *c, const unsigned int offset);
void decipher(const char *c, char *p, const unsigned int offset);

void main(){
    char a;
    int alphabet[26];
    for(int i = 0; i < 26; i++){
        alphabet[i] = 0;
    }
    FILE *file = fopen(filelocation, "r");
    if(!file){
        printf("error reading file");
    }
    while(!feof(file)){
        a = fgetc(file);
        if(isalpha(a)){
            printf("%c", toupper(a));
        }
        else{
            printf("_");
        }
    }
    fclose(file);
    printf("\n\n");
    encipher(filelocation, encrypted, OFFSET);
    printf("\n\n");
    decipher(encrypted, decrypted, OFFSET);
}

void encipher(const char *p, char *c, const unsigned int offset){
    FILE *read = fopen(p, "r");
    FILE *write = fopen(c, "w");
    char a;
    if(!read){
        printf("error reading file");
    }
    if(!write){
        printf("error writing file");
    }
    while(!feof(read)){
        a = fgetc(read);
        if(isalpha(a)){
            a = toupper(a);
            a += offset;
            if(a > 90){
                a = 64+(a-90);
            }
            if(a < 65){
                a = 90-(65-a);
            }
            fprintf(write, "%c", a);
        }
        else{
            fprintf(write, "_");
        }
    }
    fclose(read);
    fclose(write);
}

void decipher(const char *p, char *c, const unsigned int offset){
    FILE *read = fopen(p, "r");
    FILE *write = fopen(c, "w");
    int a;
    //int deoffset = -offset;
    if(!read){
        printf("error reading file");
    }
    if(!write){
        printf("error writing file");
    }
    while(!feof(read)){
        a = fgetc(read);
        // reads character from encrypted file
        if(isalpha(a)){
            a -= offset;
            if(a > 90){
                a = 64+(a-90);
            }
            if(a < 65){
                a = 90+(a-64);
            }
            fprintf(write, "%c", a);
        }
        else{
            fprintf(write, "_");
        }
    }
    fclose(read);
    fclose(write);
}
└──────────────────────────────────────────────────────────────────────────────────────┘

["3.2enc.txt:"]

______NBYLY_CM_CHXYYX_NBY_CHYRJLYMMCVFY__NBCM_MBIQM_CNMYFZ__CN_CM_NBY_GSMNCWUF________NBY_LCABN_GYNBIX_IZ_JBCFIMIJBS_QIOFX_VY_NBCM__NI_MUS_HINBCHA_YRWYJN_QBUN_WUH_VY_MUCX__C_Y__NBY_JLIJIMCNCIHM_IZ_HUNOLUF_MWCYHWY__C_Y__MIGYNBCHA_NBUN_BUM_HINBCHA_NI_XI_QCNB_JBCFIMIJBS__UHX_NBYH_UFQUSM__QBYH_MIGYIHY_YFMY_QCMBYX_NI_MUS_MIGYNBCHA_GYNUJBSM__CWUF__NI_XYGIHMNLUNY_NI_BCG_NBUN_BY_BUX_ACPYH_HI_GYUHCHA_NI_WYLNUCH_MCAHM_CH_BCM_JLIJIMCNCIHM__NBCM_GYNBIX_QIOFX_VY_OH__MUNCMZSCHA_NI_NBY_INBYL___BY_QIOFX_HIN_BUPY_NBY_ZYYFCHA_NBUN_QY_QYLY_NYUWBCHA_BCG_JBCFIMIJBS___VON_CN_QIOFX_VY_NBY_IHFS_MNLCWNFS_WILLYWN_GYNBIX________GS_JLIJIMCNCIHM_ULY_YFOWCXUNILS_CH_NBCM_QUS__BY_QBI_OHXYLMNUHXM_GY_ZCHUFFS_LYWIAHCTYM_NBYG_UM_MYHMYFYMM__QBYH_BY_BUM_WFCGVYX_ION_NBLIOAB_NBYG__IH_NBYG__IPYL_NBYG___BY_GOMN_MI_NI_MJYUE_NBLIQ_UQUS_NBY_FUXXYL__UZNYL_BY_BUM_WFCGVYX_OJ_IH_CN___BY_GOMN_MOLGIOHN_NBYMY_JLIJIMCNCIHM__NBYH_BY_MYYM_NBY_QILFX_LCABNFS_____QBYLYIZ_IHY_WUHHIN_MJYUE__NBYLYIZ_IHY_GOMN_VY_MCFYHN___BNNJM___QQQ_AONYHVYLA_ILA_ZCFYM___________JXZ_JXZ_NLUWNUNOM_FIACWI_JBCFIMIJBCWOM_FOXQCA_QCNNAYHMNYCH___

["3.2dec.txt:"]

______THERE_IS_INDEED_THE_INEXPRESSIBLE__THIS_SHOWS_ITSELF__IT_IS_THE_MYSTICAL________THE_RIGHT_METHOD_OF_PHILOSOPHY_WOULD_BE_THIS__TO_SAY_NOTHING_EXCEPT_WHAT_CAN_BE_SAID__I_E__THE_PROPOSITIONS_OF_NATURAL_SCIENCE__I_E__SOMETHING_THAT_HAS_NOTHING_TO_DO_WITH_PHILOSOPHY__AND_THEN_ALWAYS__WHEN_SOMEONE_ELSE_WISHED_TO_SAY_SOMETHING_METAPHYS__ICAL__TO_DEMONSTRATE_TO_HIM_THAT_HE_HAD_GIVEN_NO_MEANING_TO_CERTAIN_SIGNS_IN_HIS_PROPOSITIONS__THIS_METHOD_WOULD_BE_UN__SATISFYING_TO_THE_OTHER___HE_WOULD_NOT_HAVE_THE_FEELING_THAT_WE_WERE_TEACHING_HIM_PHILOSOPHY___BUT_IT_WOULD_BE_THE_ONLY_STRICTLY_CORRECT_METHOD________MY_PROPOSITIONS_ARE_ELUCIDATORY_IN_THIS_WAY__HE_WHO_UNDERSTANDS_ME_FINALLY_RECOGNIZES_THEM_AS_SENSELESS__WHEN_HE_HAS_CLIMBED_OUT_THROUGH_THEM__ON_THEM__OVER_THEM___HE_MUST_SO_TO_SPEAK_THROW_AWAY_THE_LADDER__AFTER_HE_HAS_CLIMBED_UP_ON_IT___HE_MUST_SURMOUNT_THESE_PROPOSITIONS__THEN_HE_SEES_THE_WORLD_RIGHTLY_____WHEREOF_ONE_CANNOT_SPEAK__THEREOF_ONE_MUST_BE_SILENT___HTTPS___WWW_GUTENBERG_ORG_FILES___________PDF_PDF_TRACTATUS_LOGICO_PHILOSOPHICUS_LUDWIG_WITTGENSTEIN____

3.3 ["Code Breaking"]

┌──────────────────────────────────────────────────────────────────────────────────────┐
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#define OFFSET 14

char *filelocation = "3.1.txt";
char *train1 = "data1.txt"; // An extract from through the looking glass, Lewis Carroll.
char *train2 = "data2.txt"; // I dwell in possibility, Emily Dickinson.
char *train3 = "data3.txt"; // Immanuel Kant, Critique of Pure Reason.
char *train4 = "data4.txt"; // Miyazawa Kenji, Night on the Galactic Railroad.
char *train5 = "data5.txt"; // SCA-DI, Sakura no Uta
char *encrypted = "3.4enc.txt";
char *decrypted = "3.4dec.txt";

void calculateHistogram(char *filename, int *alphabetarray);
void printValue(const int *alphanum);
void plot(const int *alphanum, int width);
void encipher(const char *p, char *c, const unsigned int offset);
void decipher(const char *c, char *p, const unsigned int offset);
void training(int *alphabet);
int calculateOffset(const int *test, const int *data);

void main(){
    char a;
    int trainingdata[26];
    int alphabet[26];
    for(int i = 0; i < 26; i++){
        alphabet[i] = 0;
        trainingdata[i] = 0;
    }
    encipher(filelocation, encrypted, OFFSET);
    calculateHistogram(encrypted, alphabet);
    training(trainingdata);
    printValue(trainingdata);
    printf("\n");
    printValue(alphabet);
    printf("\n");
    printf("%d", calculateOffset(alphabet, trainingdata));
    decipher(encrypted, decrypted, calculateOffset(alphabet, trainingdata));

}

int calculateOffset(const int *test, const int *data){
    int highesttest = 0;
    int highestlearned = 0;
    int testarraypos = 0;
    int learnedarraypos = 0;
    for(int i = 0; i < 26; i++){
        if(test[i] > highesttest){
            highesttest = test[i];
            testarraypos = i;
        }
        if(data[i] > highestlearned){
            highestlearned = data[i];
            learnedarraypos = i;
        }
    }
    return testarraypos - learnedarraypos;
}

void training(int *alphabet){
    char a;
    for(int i = 0; i < 26; i++){
        alphabet[i] = 0;
    }
    calculateHistogram(train1, alphabet);
    calculateHistogram(train2, alphabet);
    calculateHistogram(train3, alphabet);
    calculateHistogram(train4, alphabet);
    calculateHistogram(train5, alphabet);
}

void calculateHistogram(char *fn, int *arr){
    char a;
    FILE *file = fopen(fn, "r");
    if(!file){
        printf("error reading file");
    }
    while(!feof(file)){
        a = fgetc(file);
        if(isalpha(a)){
            a = toupper(a);
            // printf("\n");
            //printf("%d, ", a);
            arr[a-65] += 1;
            //printf("%d, ", arr[a-65]);
        }
        else{}
    }
    fclose(file);
}

void printValue(const int *arr){
    for(int i = 0; i < 26; i++){
        printf("%d\n", arr[i]);
    }
}

void encipher(const char *p, char *c, const unsigned int offset){
    FILE *read = fopen(p, "r");
    FILE *write = fopen(c, "w");
    char a;
    if(!read){
        printf("error reading file");
    }
    if(!write){
        printf("error writing file");
    }
    while(!feof(read)){
        a = fgetc(read);
        if(isalpha(a)){
            a = toupper(a);
            a += offset;
            if(a > 90){
                a = 64+(a-90);
            }
            if(a < 65){
                a = 90-(65-a);
            }
            fprintf(write, "%c", a);
        }
        else{
            fprintf(write, "_");
        }
    }
    fclose(read);
    fclose(write);
}

void decipher(const char *p, char *c, const unsigned int offset){
    FILE *read = fopen(p, "r");
    FILE *write = fopen(c, "w");
    int a;
    //int deoffset = -offset;
    if(!read){
        printf("error reading file");
    }
    if(!write){
        printf("error writing file");
    }
    while(!feof(read)){
        a = fgetc(read);
        // reads character from encrypted file
        if(isalpha(a)){
            a -= offset;
            if(a > 90){
                a = 64+(a-90);
            }
            if(a < 65){
                a = 90+(a-64);
            }
            fprintf(write, "%c", a);
        }
        else{
            fprintf(write, "_");
        }
    }
    fclose(read);
    fclose(write);
}
└──────────────────────────────────────────────────────────────────────────────────────┘

After testing with many different texts, this method does work fairly well the longer the text is as essentially all it is looking for is the "position" of the character E, since E seems to be the one that comes up the most in English.

4 ["Optional Additional Work"]

Incorporating a varying offset using a word.
┌──────────────────────────────────────────────────────────────────────────────────────┐
#include <stdio.h>
#include <ctype.h>
#include <math.h>

char *filelocation = "3.1.txt";
char *encrypted = "4enc.txt";
char *decrypted = "4dec.txt";
char word[] = "TEST";
// 4 letter phrases only

void encipher(const char *p, char *c, const char *word);
void decipher(const char *c, char *p, const char *word);

void main(){
    char a;
    int alphabet[26];
    for(int i = 0; i < 26; i++){
        alphabet[i] = 0;
    }
    FILE *file = fopen(filelocation, "r");
    if(!file){
        printf("error reading file");
    }
    while(!feof(file)){
        a = fgetc(file);
        if(isalpha(a)){
            printf("%c", toupper(a));
        }
        else{
            printf("_");
        }
    }
    fclose(file);
    printf("\n\n");
    encipher(filelocation, encrypted, word);
    printf("\n\n");
    decipher(encrypted, decrypted, word);
}

void encipher(const char *p, char *c, const char *word){
    FILE *read = fopen(p, "r");
    FILE *write = fopen(c, "w");
    char a;
    int offset = 0;
    int pos = 0;
    if(!read){
        printf("error reading file");
    }
    if(!write){
        printf("error writing file");
    }
    while(!feof(read)){
        a = fgetc(read);
        switch (pos)
        {
            case 0:
                pos = 1;
                break;
            case 1:
                pos = 2;
                break;
            case 2:
                pos = 3;
                break;
            case 3:
                pos = 0;
                break;
        }
        offset = floor(word[pos]/4);
        printf("offset: %d\n", offset);
        if(isalpha(a)){
            a = toupper(a);
            a += offset;
            if(a > 90){
                a = 64+(a-90);
            }
            if(a < 65){
                a = 90-(65-a);
            }
            fprintf(write, "%c", a);
        }
        else{
            fprintf(write, "_");
        }
    }
    fclose(read);
    fclose(write);
}

void decipher(const char *p, char *c, const char *word){
    FILE *read = fopen(p, "r");
    FILE *write = fopen(c, "w");
    int a;
    int offset = 0;
    int pos = 0;
    if(!read){
        printf("error reading file");
    }
    if(!write){
        printf("error writing file");
    }
    while(!feof(read)){
        a = fgetc(read);
        switch (pos)
        {
            case 0:
                pos = 1;
                break;
            case 1:
                pos = 2;
                break;
            case 2:
                pos = 3;
                break;
            case 3:
                pos = 0;
                break;
        }
        offset = floor(word[pos]/4);
        if(isalpha(a)){
            a -= offset;
            if(a > 90){
                a = 64+(a-90);
            }
            if(a < 65){
                a = 90+(a-64);
            }
            fprintf(write, "%c", a);
        }
        else{
            fprintf(write, "_");
        }
    }
    fclose(read);
    fclose(write);
}
└──────────────────────────────────────────────────────────────────────────────────────┘

By changing the offset for every character using a 4 letter word, the encrypted text is far more difficult to decipher by just looking at it:

"______OCVLZ_ZM_DEXZZU_OCV_DIVRKMVMNDSFZ__NCDJ_NCFQN_ZNNZCZ__ZN_DJ_OCV_HTJNDXRF________OCV_MDXBO_DYOCFX_JW_KCZFJNFJCT_QJPCX_WV_OCZM__KI_NRS_IFNCDEA_ZOWZKK_RCRN_XRH_WV_NVZX__Z_Z__NCZ_JMJGINDKCJIJ_JA_HVOLLVG_MXDVHXZ__D_V__NFGZOYCIB_NCVK_CVJ_IJKBDIX_OJ_XJ_NCOC_JCDCINJGBT__UIY_NCZE_VGNUTN__RCVH_NFGZJEY_ZCMZ_NCNCVX_OF_NVP_NJDYOCZHB_DYOVGBTN__DXRF__KI_YVGJIJNMVKY_OF_CDD_OCRN_CV_CVU_BDMYI_EI_HVUIDEA_OF_XZINVDE_NDXHN_ZH_CZM_KIIKJJCODFHN__NCDJ_HZKBJY_QJPCX_WV_PI__NVKCNAPCIB_NJ_KBZ_FNCZI___YY_RFOGY_HJO_BVQV_OCV_AZVFDIX_OCRN_RV_RZIY_OVUXCZHB_YCH_GBDGFMJKYS___VPO_CO_NIPGU_WZ_NCZ_IIGP_NOICXOCS_XFLMZTN_HVNCJU________GT_GLJKFMDOZIIN_UMZ_YGPTCYVKIMT_CI_KBDN_QVT__CZ_QCJ_OIYVLNORHYN_GZ_WCIVCFT_IYXJXHDUVM_OYYH_RM_NVHNZCYNN__RCVH_CV_CVJ_XGZGWZU_JPK_OCIIPBY_OCVG__FH_OYYH__IQZI_OCVG___BZ_DONO_MJ_KI_NGYVF_NCMFQ_VNUT_KBZ_CUYYVL__RZOZI_CZ_BVN_WGDDVZY_OK_FH_DK___YY_HLMO_JOMHFOIO_NCZJY_KIIKJJCODFHN__NCZE_CZ_MZZJ_OCV_RJIFY_ICBCKFT_____NBZMVIA_FHZ_TUIIFN_NGYVF__OCVLZJW_JIV_HPJN_WV_NDCYIO___CKNKN___RNQ_BLNZISYMB_IMB_ZDGVM___________JYA_JYA_NMVTNVOLM_GFADXF_KCZFJNFJCDTON_COYRZA_RZNOBVHNOVCI___"

You can clearly see that characters that were the same before

"______NBYLY_CM_CHXYYX_NBY_CHYRJLYMMCVFY__NBCM_MBIQM_CNMYFZ__CN_CM_NBY_GSMNCWUF________N"

are no longer the same, making it much more difficult to identify.

