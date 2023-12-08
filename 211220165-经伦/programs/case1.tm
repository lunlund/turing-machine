#Q = {q,q0,q1,q2,q3,q4,q5,q6,q7,q8,p0,p1,rej,rej1,rej2,rej3,rej4,rej5,rej6,rej7,rej8,rej9,rej10,rej11,rej12,halt_reject,accept}
#S = {a,b}
#G = {a,b,c,_,I,l,e,g,a,n,p,u,t}
#q0 = q
#B = _
#F = {accept}
#N = 2

q a_ __ r* q0
q b_ __ r* p0
q __ __ r* p0
q0 a_ a_ r* q0
q0 b_ cc rr q1
q0 _* _* l* p1

q1 b_ cc rr q1
q1 a_ a_ r* p0

p0 a* a* r* p0
p0 b* b* r* p0
p0 c* c* r* p0
p0 _* _* l* p1

p1 a* _* l* p1
p1 b* _* l* p1
p1 c* _* l* p1
p1 _* _* ** rej

rej _* I* r* rej1
rej1 _* l* r* rej2
rej2 _* l* r* rej3
rej3 _* e* r* rej4
rej4 _* g* r* rej5
rej5 _* a* r* rej6
rej6 _* l* r* rej7
rej7 _* _* r* rej8
rej8 _* I* r* rej9
rej9 _* n* r* rej10
rej10 _* p* r* rej11
rej11 _* u* r* rej12
rej12 _* t* ** halt_reject

q1 __ __ ll q2
q2 cc cc ll q2
q2 a_ a_ lr q3
q2 __ __ r* q4
q3 a* a* l* q3
q3 _* _* r* q4

q4 a* _* r* q5
q5 a* a* r* q5
q5 c* c* r* q5
q5 _c cc rr q6
q6 _c cc rr q6
q6 __ __ ll q7
q7 cc cc ll q7
q7 c_ c_ lr q8
q8 c* c* l* q8
q8 a* a* l* q8
q8 _* _* r* q4

q4 c* c* ** accept
