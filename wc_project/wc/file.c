void none()//ͳ�ƿ�����
{
	int i,j = 0;
	for (i = 0;; i++)
	{
		if (art[i] == EOF)
			break;
		if (art[i] != '\n'&& art[i] != '\t'&& art[i] != ' ')
		{
			j++;
			//ͳ�Ƶ�������������ע������//ͳ�Ƶ�������������ע������//ͳ�Ƶ�������������ע������//ͳ�Ƶ�������������ע������
			//ͳ�Ƶ�������������ע������
		}
		if (art[i] == '\n')
		{
			if (j <= 1)
				none_num++;
			j = 0;
		}
	}
}
//ͳ�Ƶ�������������ע������
int count()
{
	//ͳ�Ƶ�������������ע������
	get();
	clearToken();
	//ͳ�Ƶ�������������ע������
	while (isSpace(ch) || isNewline(ch) || isTab(ch) || isComma(ch))
	{
		if (isNewline(ch)) line_num++;
		get();
	}
	if (isStar(ch))
	{
		catToken(ch);
		//ͳ�Ƶ�������������ע������
	}
	else if (isDivi(ch))
	{
		catToken(ch);
		get();
		//ͳ�Ƶ�������������ע������
		if (isStar(ch))
		{
			note_num++;
			catToken(ch);
			do
			{
				do
				{
					get();
					if (isNewline(ch))
					{
