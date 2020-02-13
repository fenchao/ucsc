/************************************************************************/
/****************                  prologue               ***************/ 
/*                                                                      */
/*              University of California Extension, Santa Cruz          */
/*                                                                      */
/*                          Advanced C Programming                      */
/*                                                                      */
/*                    Instructor: Rajainder A. Yeldandi                 */
/*                                                                      */
/*    Author: Fenchao Du                                                */
/*                                                                      */
/*    Assignment Number: 4                                              */
/*                                                                      */
/*    Topic: Student & Class Grading                                    */
/*                                                                      */
/*    file name: score.c                                                */ 
/*                                                                      */
/*    Date: 07/08/2017                                                  */
/*                                                                      */
/*    Objective: compute and print stats for each student and class     */
/*                                                                      */
/*    Comments: input file must have 60 scores                          */
/*                                                                      */
/************************************************************************/ 

#include <stdio.h>

#define DEFAULT_ID 1000
#define NUM_SCORE 60
#define INPUT_FILE_PATH "score.txt"
#define OUTPUT_FILE_PATH "stats.txt"

/* assign student id starting from 1000 */
int assign_id(void)
{
    static int id = DEFAULT_ID;
    return id++;
}

/* print letter grade for each score */
void print_letter_grade(int score, FILE *fp)
{
    fprintf(fp, "%d:", score);
    if (score > 95) {
        fprintf(fp, "A+");
    } else if (score == 95) {
        fprintf(fp, "A");
    } else if (score >= 90) {
        fprintf(fp, "A-");
    } else if (score > 85) {
        fprintf(fp, "B+");
    } else if (score == 85) {
        fprintf(fp, "B");
    } else if (score >= 80) {
        fprintf(fp, "B-");
    } else if (score > 75) {
        fprintf(fp, "C+");
    } else if (score == 75) {
        fprintf(fp, "C");
    } else if (score >= 70) {
        fprintf(fp, "C-");
    } else if (score >= 60) {
        fprintf(fp, "D");
    } else {
        fprintf(fp, "F");
    }
}

int main (void)
{
    int i, j, num;
    int c_min, c_max, c_sum = 0; /* class min, max, sum */
    FILE *ifp, *ofp;

    /* open score input and output file */
    ifp = fopen(INPUT_FILE_PATH, "r");
    ofp = fopen(OUTPUT_FILE_PATH, "w");

    /* learn how many students in this class */
    printf("give the number of students: ");
    scanf("%d", &num);

    /* for each student */
    for (i = 0; i < num; i++)
    {
        int min, max, sum = 0; /* student min, max, sum */

        /* assign id */
        fprintf(ofp, "\nStudent %d:\n", assign_id());

        /* read & compute each score */
        for (j = 0; j < NUM_SCORE/num; j++)
        {
            int tmp_score;
            fscanf(ifp, "%d,", &tmp_score);

            /* Assign a letter grade for each score and print */
            print_letter_grade(tmp_score, ofp);
            if (j + 1 == NUM_SCORE/num) {
                fprintf(ofp, "\n");
            } else {
                fprintf(ofp, ", ");
            }

            if (j == 0 && i == 0) {
                /* initialize class */
                c_min = tmp_score;
                c_max = tmp_score;
                c_sum = tmp_score;
            } else {
                /* compute class score stat */
                c_min = tmp_score < c_min ? tmp_score : c_min;
                c_max = tmp_score > c_max ? tmp_score : c_max;
                c_sum += tmp_score;
            }

            if (j == 0) {
                /* initialize student */
                min = tmp_score;
                max = tmp_score;
                sum = tmp_score;
            } else {
                /* compute student score stat */
                min = tmp_score < min ? tmp_score : min;
                max = tmp_score > max ? tmp_score : max;
                sum += tmp_score;
            }
        }

        /* print student stat */
        fprintf(ofp, "min %d, max %d, average %d\n", min, max, sum*num/NUM_SCORE);
    }

    /* print class stat */
    fprintf(ofp, "\nClass: min %d, max %d, average %d\n", c_min, c_max, c_sum/NUM_SCORE);

    /* close input and output file*/
    fclose(ifp);
    fclose(ofp);

    return 0;
}
