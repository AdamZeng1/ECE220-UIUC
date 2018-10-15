
#include <stdio.h>


#include "cmp_mat.h"
#ifndef SP_MAT
#define SP_MAT
#include "sparsemat.h"
#endif

int main(int argc, char *argv[]){

	printf("calling load_lils on \"matrices/input_mats/scrambled_rows.txt\":\n");
	sp_lils * unscrambledrowst = load_lils("matrices/input_mats/scrambled_rows.txt");
	printl(unscrambledrowst);
	
	printf("calling load_lils on \"matrices/input_mats/scrambled_rows_large.txt\":\n");
	sp_lils * unscrambledrowstlarge = load_lils("matrices/input_mats/scrambled_rows_large.txt");
	printl(unscrambledrowstlarge);
	
	printf("calling load_lils on \"matrices/input_mats/withZeroes.txt\":\n");
	sp_lils * withZeroest = load_lils("matrices/input_mats/withZeroes.txt");
	printl(withZeroest);
	
	sp_lils * a_At = load_lils("matrices/input_mats/a_A.txt");
	sp_lils * a_Bt = load_lils("matrices/input_mats/a_B.txt");
	printf("a_Ct = a_A+a_B addition in lils:\n");
	sp_lils * a_Ct = add_lils(a_At,a_Bt);
	printl(a_Ct);
	
	sp_lils * sa_At = load_lils("matrices/input_mats/sa_A.txt");
	sp_lils * sa_Bt = load_lils("matrices/input_mats/sa_B.txt");
	printf("sa_Ct = sa_A+sa_B sparse addition in lils:\n");
	sp_lils * sa_Ct = add_lils(sa_At,sa_Bt);
	printl(sa_Ct);

	//very large sparese matrices addition
	sp_lils * sla_A = load_lils("matrices/input_mats/sla_A.txt");
	sp_lils * sla_B = load_lils("matrices/input_mats/sla_B.txt");
	printf("sla_C = sla_A+sla_B sparse addition in lils:\n");
	sp_lils * sla_C = add_lils(sla_A,sla_B);
	printl(sla_C);
	
/*
	sp_lils * m_At = load_lils("matrices/input_mats/m_A.txt");
	sp_lils * m_Bt = load_lils("matrices/input_mats/m_B.txt");
	printf("m_Ct = m_A*m_B multiplication in lils:\n");
	sp_lils * m_Ct = mult_lils(m_At,m_Bt);
	printl(m_Ct);
	
	sp_lils * sm_At = load_lils("matrices/input_mats/sm_A.txt");
	sp_lils * sm_Bt = load_lils("matrices/input_mats/sm_B.txt");
	printf("sm_Ct = sm_A*sm_B sparse multiplication in lils:\n");
	sp_lils * sm_Ct = mult_lils(sm_At,sm_Bt);
	printl(sm_Ct);

	//very large sparese matrices multiplication
	sp_lils * sml_A = load_lils("matrices/input_mats/sml_A.txt");
	sp_lils * sml_B = load_lils("matrices/input_mats/sml_B.txt");
	printf("sml_C = sml_A*sml_B sparse multiplication in lils:\n");
	sp_lils * sml_C = mult_lils(sml_A,sml_B);
	printl(sml_C);
*/



	printf("Saving output matrices... \n");
	
	save_lils("matrices/output_mats/withZeroest.txt",withZeroest);
	save_lils("matrices/output_mats/unscrambled.txt",unscrambledrowst);
	save_lils("matrices/output_mats/unscrambledlarge.txt",unscrambledrowstlarge);
	save_lils("matrices/output_mats/a_Ct.txt",a_Ct);
	save_lils("matrices/output_mats/sa_Ct.txt",sa_Ct);
	save_lils("matrices/output_mats/sla_C.txt",sla_C);
/*
	save_lils("matrices/output_mats/m_Ct.txt",m_Ct);
	save_lils("matrices/output_mats/sm_Ct.txt",sm_Ct);
	save_lils("matrices/output_mats/sml_C.txt",sml_C);	
*/

    printf("freeing matrices from memory..\n");
	destroy_lils(withZeroest);
	destroy_lils(unscrambledrowst);
	destroy_lils(unscrambledrowstlarge);

	destroy_lils(a_At);
	destroy_lils(sa_At);
	destroy_lils(sla_A);

	destroy_lils(a_Bt);
	destroy_lils(sa_Bt);
	destroy_lils(sla_B);

	destroy_lils(a_Ct);
	destroy_lils(sa_Ct);
	destroy_lils(sla_C);

/*
	//destroy_lils(m_At);
	//destroy_lils(sm_At);
	//destroy_lils(sml_A);

	//destroy_lils(m_Bt);
	//destroy_lils(sm_Bt);
	//destroy_lils(sml_B);

	//destroy_lils(m_Ct);
	//destroy_lils(sm_Ct);
	//destroy_lils(sml_C);
*/

    return 0;
}
