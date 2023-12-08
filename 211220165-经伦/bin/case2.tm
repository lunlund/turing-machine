#Q = {q0,q1,q2,q3,q4,q5,q6,q7,q8,q9,accept,accept2,accept3,accept4,halt_accept,reject,reject2,reject3,reject4,reject5,halt_reject}
#S = {a,b,c}
#G = {a,b,c,_,t,r,u,e,f,a,l,s,e}
#q0 = q0
#B = _
#F = {halt_accept}
#N = 1

q0 a _ r q1
q0 b _ r q2
q0 c _ r q7
q0 _ _ r reject

q1 a a r q1
q1 b b r q1
q1 c c r q1
q1 _ _ l q3

q3 a _ l q5
q3 b _ l q8
q3 c _ l q8
q3 _ _ * reject

q5 a a l q5
q5 b b l q5
q5 c c l q5
q5 _ _ r q0

q2 a a r q2
q2 b b r q2
q2 c c r q2
q2 _ _ l q4

q4 b _ l q6
q4 a _ l q8
q4 c _ l q8
q4 _ _ * reject

q6 a a l q6
q6 b b l q6
q6 c c l q6
q6 _ _ r q0

q7 _ _ * accept
q7 a _ r q9
q7 b _ r q9
q7 c _ r q9

q8 a _ l q8
q8 b _ l q8
q8 c _ l q8
q8 _ _ l reject

q9 a _ r q9
q9 b _ r q9
q9 c _ r q9
q9 _ _ r reject

reject _ f r reject2
reject2 _ a r reject3
reject3 _ l r reject4
reject4 _ s r reject5
reject5 _ e * halt_reject

accept _ t r accept2
accept2 _ r r accept3
accept3 _ u r accept4
accept4 _ e * halt_accept
