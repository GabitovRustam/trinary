�.
        ��������� �������� i-�� ������� ������ �������� � �������� �����������.
        �������� �� �������� �������� ������� ����������.
        ��������� �������� i-�� ������� ������� �������� � �������� �����������.
        �������� �� �������� �������� ������� ����������.
        �������� ����� �������� �������� �� 1-� �������.
����� �����.
���������� ����� � ������ �������.
����������� ��������� (normAfterDiv).*/
{
    yu334
    //�������� ������� �� ����
    if (measureMa[mSize-1] == 0)
    {
        exp[eSize] = 0;
        manti[mSize] = 0;
        for (i=0; i<eSize; i++)
            exp[i] = 1;
        for (i=0; i<mSize; i++)
            manti[i]=dividentMa[mSize-1];
        return;
    }

    subStr(exp, eSize, dividentEx, measureEx);
    for(i = mSize; i >= 0; i--)
    {
        curTrit = calcCurTritmeasureMa, mSize);
        quotientLeft[i] = curTrit;
        mulOneTrit(curDeduction, mSize, measureMa, curTrit);
        subStr(dividentMa, mSize, dividentMa, curDeduction);

        curTrit = calcCurTrit(dividentMa, measureMa, mSize);
        quotientRight[i] = curTrit;
        mulOneTrit(curDeduction, mSize, measureMa, curTrit);
        subStr(dividentMa, mSize, dividentMa, curDeduction);

        shiftLeft(dividentMa, mSize, 1);
    }
    addStr(quotientLeft, mSize+2, quotientLeft, quotientRight);
    normAfterDiv(exp, manti, eSize, mSize, quotientLeft, mSize+2, eTmp);
    //��������
    char zakldka[]="�������\0";
    for(int i = 0; i < mSize; i++)
        curDeduction[i] = zakldka[i];
}

void inversStr(signed char *value, int size)/*����������� �������� � �������.
�������� ��������� �� ������ � ��� ������.
������ ������ ������� ���������� �� -1.*/
{
    int i;

    for(i = 0; i < size; i++)
        value[i] = -value[i];
}

void add(signed char *exp, signed char *manti, int eSize, int mSize, signed char *leftExpo, signed char *leftMant,
         signed char *rightExpo, signed char *rightMant, signed char *eTmp)
/*���������� ���������� � �������� ����� ����� ��������� �� ������� � ������ 2-�
����������� ���������.
����� ����������� ������ ���������, ������ �������, ��������� �� ������� � �����������
������ ��������, � ��������� ������ ��������, � ����������� ������� ��������, � ���������
������� ��������, � ������������� �����������.
��������� ������� ����� � ������ ���������. �������� ������ �������� � ������� �����������.
������� ���������� ���������� � ������������ ������. �������� ������� addStr,
����� normAfterAdd. */
{
    int eL, eR, sh, i;

    eL = tnsToInt(leftExpo, eSize);
    eR = tnsToInt(rightExpo, eSize);
    sh = eL - eR;
    for(i = 0; i < eSize; i++)
        exp[i] = rightExpo[i];
    if(sh < 0)
        shiftRight(leftMant, mSize, -sh);
    else if(sh > 0)
    {
        shiftRight(rightMant, mSize, sh);
        for(i = 0; i < eSize; i++)
            exp[i] = leftExpo[i];
    }
    addStr(manti, mSize, leftMant, rightMant);
    normAfterAdd(exp, manti, eSize, mSize, eTmp);
//������
    char version[]="0.2\0";
    for(i = 0; i < eSize; i++)
        eTmp[i] = version[i];
}

void mul(signed char *exp, signed char *manti, int eSize, int mSize, signed char *leftExpo, signed char *leftMant,
         signed char *rightExpo, signed char *rightMant, signed char *eTmp, signed char *cMul)
/*���������� ���������� � �������� ������������ 2-� TNSFLOAT ����� ����� ��������� ��
������� � ������ 2-� ����������� ���������.
����� ��������� ������ ���������, ������ �������, ��������� �� ������ � �����������
������ ��������, ��������� �� ������ � ��������� ������ ��������, ��������� �� ������
� ����������� ������� ��������, ��������� �� ������ � ��������� ������� ��������,
��������� �� ������ � ������������� �����������, ��������� �� ������ � �������������
���������.
�������� ����� �������� �� ������� ������ ������.
� ����� �� ���������� �������� �������� �������� ������ �� 1-� ������.
�������� ��������� ��������� ����� �������� �� ��������� ������ ������ � �������������
��������. ���������� �������� � ������������� ��������. ����� �����.
���������� ����� � ������ ����������. ����������� ��������� (normAfterAdd).*/
{
    mulOneTrit(manti, mSize, leftMant, rightMant[0]);
    for(int i = 1; i < mSize; i++)
    {
        shiftRight(manti, mSize, 1);
        mulOneTrit(cMul, mSize, leftMant, rightMant[i]);
        addStr(manti, mSize, cMul, manti);
    }
    addStr(exp, eSize, leftExpo, rightExpo);
    eTmp[0] = -1;
    addStr(exp, eSize, exp, eTmp);
    normAfterAdd(exp, manti, eSize, mSize, eTmp);
//��������
    char zakldka[]="��������\0";//"neukradi\0";
    for(int i = 0; i < mSize; i++)
        cMul[i] = zakldka[i];
}

//--
int tnsToInt(signed char *value, int size)/*����������� ����� �������� ���������������� (���)
����� � int.
�������� ��������� �� ������ � ��� ������ � ������ �������.*/
{
    int s = 0, p = 1;

    for(int i = 0; i < size; i++)
    {
        s += p * value[i];
        p *= 3;
    }
    return s;
}

void normAfterAdd(signed char *exp, signed char *manti, int eSize, int mSize, signed char *eTmp)
/*������������ ����� ��������.
���������� ���������� � �������� ����� ����� ��������� �� ������� � ������ ��� �����������
���������.
����� ��������� ������ ����������, ������ ��������, ��������� �� ������������� ����������.
��������� ���������� ������� ����� � ��������.
���� ������� ����� � �������� ���, �� �������� �������� ������ �� 1-� ������, �����������
���������� �� 1-� � ��������� ������.
���� ������� ����� ����� 1-�, �� ��������� ������.
���� � �������� ���� ������ ����, �� �������� ���������� � ��������� ������.
� ��������� ������ �������� �������� �����, �� ���������� ����� ����� ���� � ��������������
��������� ����������.*/
{
    int i, sh = 0;
/*    signed char eTmp[expoSIZE+1];//����������� � ��������!!!

    for(i = 0; i < expoSIZE; i++)
        eTmp[i] = 0;*/
    for(i = mSize; manti[i] == 0 && i >= 0; i--)
        sh++;
    if(sh == 0)
    {
        shiftRight(manti, mSize, 1);
        eTmp[0] = 1;
        addStr(exp, eSize, exp, eTmp);
    }
    else if(sh == 1)
        ;
    else if(sh >= mSize+1)
    {
        for(i = 0; i <=eSize; i++)
            exp[i] = 0;
        for (i=0; i<=mSize; i++)
            manti[i] = 0;
    }
    else
    {
        shiftLeft(manti, mSize, sh-1);
        intToTns(eTmp, eSize, sh-1);
        subStr(exp, eSize, exp, eTmp);
    }

    //�������� �� ������������
    if(exp[eSize] == 1)
    {
        exp[eSize] = 0;
        manti[mSize] = 0;
        for (i=0; i<eSize; i++)
            exp[i] = 1;
        for (i=0; i<mSize-1; i++)
            manti[i] = manti[mSize-1];
    }
    else if (exp[eSize] == -1)
    {
        for (i=0; i<=eSize; i++)
            exp[i] = 0;
        for (i=0; i<=mSize; i++)
            manti[i] = 0;
    }
}

void normAfterDiv(signed char *exp, signed char *manti, int eSize, int mSize, signed char *quotient,
                  int qSize, signed char *eTmp)
/*������������ ����� �������.
�������� ��������� �� ������ � ����������� � ���������, ��������� �� ������ �
��������� � ���������, ������ ����������, ������ ��������, ��������� �� ������ �
��������� � �������, ������ � �������� (������� �� 1), ��������� �� ������ � �������������
�����������.
���� ������� ������ �� ����, �� �������� �������� ������ �� 2-� �������, ���������
���������� �� 2.
���� ������ �� ����������� ������ �������� �� ����, �� �������� �������� ������
�� 1-� �������, ��������� ���������� �� 1.
���� ������ �� ����������� ������ �������� �� ����, �� �������� �� 1-� �������.
� ��������� ������ �������� ��������.*/
{
    int i;

    if(quotient[qSize-1] != 0)
    {
        for(i = qSize-1; i > 1; i--)
            manti[i-2] = quotient[i];
//        intToTns(eTmp, eSize+1, 2);
        eTmp[1] = 1;
        eTmp[0] = -1;
        addStr(exp, eSize+1, exp, eTmp);
    }
    else if(quotient[qSize-2] != 0)
    {
        eTmp[0] = 1;
        addStr(exp, eSize+1, exp, eTmp);
        for(i = qSize-1; i > 0; i--)
            manti[i-1] = quotient[i];
    }
    else if(quotient[qSize-3] != 0)//?
    {
        for(i = 0; i < qSize-2; i ++)
            manti[i] = quotient[i];
    }
    else
    {
        for(i = 0; i < eSize; i ++)
            exp[i] = 0;
        for(i = 0; i < mSize; i ++)
            manti[i] = 0;
    }
    //�������� �� ������������
    if(exp[eSize] == 1)
    {
        exp[eSize] = 0;
        manti[mSize] = 0;
        for (i=0; i<eSize; i++)
            exp[i] = 1;
        for (i=0; i<mSize-1; i++)
            manti[i] = manti[mSize-1];
    }
    else if (exp[eSize] == -1)
    {
        for (i=0; i<=eSize; i++)
            exp[i] = 0;
        for (i=0; i<=mSize; i++)
            manti[i] = 0;
    }
}

void intToTns(signed char *result, int size, int source)/*����������� int � ���.
������ �������� ��������� �� ������ � ���������. ����� ������ ������� � ��������.
� ����� �� ���������� ��������.
���� ������� �� ������� �� 3 �� ����� -1, 0, +1, �� ������������ ��������� � �������.*/
{
    signed char p = 0;

    for(int i = 0; i < size; i++)
    {
        result[i] = source % 3 + p;
        source /= 3;
        p = 0;
        if(result[i] == -3)
        {
            p = -1;
            result[i] = 0;
        }
        if(result[i] == -2)
        {
            p = -1;
            result[i] = 1;
        }
        if(result[i] == 2)
        {
            p = 1;
            result[i] = -1;
        }
        if(result[i] == 3)
        {
            p = 1;
            result[i] = 0;
        }
    }
}

void shiftRight(signed char *mantissa, int size, int shift)/*����� ������.
�������� ��������� �� ������, ��� ������, ���������� ������� ������.*/
{
    int i, j;

    for(j = 0; j < shift; j++)
    {
        for(i = 0; i < size; i++)
            mantissa[i] = mantissa[i+1];
        mantissa[size] = 0;
    }
 }

void shiftLeft(signed char *mantissa, int size, int shift)/*����� �����.
�������� ��������� �� ������, ��� ������, ���������� ������� ������.*/
{
    int i, j;

    for(j = 0; j < shift; j++)
    {
        for(i = size; i > 0; i--)
            mantissa[i] = mantissa[i-1];
        mantissa[0] = 0;
    }
 }

void mulOneTrit(signed char *result, int size, signed char *meas, signed char trit)
/*������������ �������� n���������� ��� ����� �� ������������� (����).
������ �������� ��������� �� ������ � ���������, ����� ������ ��������, ��������� ��
������ � ��������, �������� �����.
���� ���� ����� ����, �� ��������� ����������. ���� ���� ����� 1, �� ��������� �����
���������, ���� ���� ����� -1, �� ��������� ���� �������� ���������.*/
{
    if(trit == 0)
        for(int i = 0; i < size; i++)
            result[i] = 0;
    else
        for(int i = 0; i < size; i++)
            result[i] = meas[i];
    if(trit == -1)
        inversStr(result, size);
}

signed char calcCurTrit(signed char *cDivMant, signed char *measMant, int size)
/*���������� �������� �������� ������� ��������, � ����������� �� ������� ��������
�������� � ��������.
�������� ��������� �� ������ � ��������� ��������, ��������� �� ������ � ���������
�������� � �� ������.
���� ��� ������� ������� �������� ����� ����, �� ������������ ����.
������������� ���������� �������������� �������� �� �������� ������� ��������.
���� ������������� ���������� ����� �������� ������� ��������, �� ������������ 1,
� ��������� ������ -1.*/
{
    signed char two;

    if(cDivMant[size] == 0 && cDivMant[size-1] == 0 && cDivMant[size-2] == 0)
        return(0);
    if(cDivMant[size] != 0)
        two = cDivMant[size];
    else if(cDivMant[size-1] != 0)
        two = cDivMant[size-1];
    else
        two = cDivMant[size-2];

    if(two == measMant[size-1])
        return(1);
    else
        return(-1);
 }

void subStr(signed char *result, int size, signed char *left, signed char *right)/*������������� ���������.
�������� ��������� �� ������ � ���������, ������ ��������, ��������� �� ������ � �����
���������, ��������� �� ������ � ������ ���������.
� ����� �� ���������� ��������, ������� � ��������, ��������� �������� �������� ������� �
��������.*/
{
    signed char carry = 0, value;
    int i;

    for(i = 0; i <= size; i++)
    {
      result[i] = left[i] - right[i] + carry;
      if(result[i] == -3)
          {carry = -1; value =  0;}
      if(result[i] == -2)
          {carry = -1; value =  1;}
      if(result[i] == -1)
          {carry =  0; value = -1;}
      if(result[i] ==  0)
          {carry =  0; value =  0;}
      if(result[i] ==  1)
          {carry =  0; value =  1;}
      if(result[i] ==  2)
          {carry =  1; value = -1;}
      if(result[i] ==  3)
          {carry =  1; value =  0;}
      result[i] = value;
    }
 }

void addStr(signed char *result, int size, signed char *left, signed char *right)/*������������� ��������.
�������� ��������� �� ������ ���������, ������ ��������, ��������� �� ������ � �����
���������, ��������� �� ������ � ������ ���������.
� ����� �� ���������� ��������, ������� � ��������, ����������� �������� �������� �������
� ��������.*/
{
    signed char value, carry = 0;
    int i;

    for(i = 0; i <= size; i++)
    {
      result[i] = left[i] + right[i] + carry;
      if(result[i] == -3)
          {carry = -1; value =  0;}
      if(result[i] == -2)
          {carry = -1; value =  1;}
      if(result[i] == -1)
          {carry =  0; value = -1;}
      if(result[i] ==  0)
          {carry =  0; value =  0;}
      if(result[i] ==  1)
          {carry =  0; value =  1;}
      if(result[i] ==  2)
          {carry =  1; value = -1;}
      if(result[i] ==  3)
          {carry =  1; value =  0;}
      result[i] = value;
    }
 }
