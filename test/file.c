void none()
//ͳ�ƿ�����
{
	int i,j = 0;
	for (i = 0;; i++)
	{
		if (art[i] == EOF)
			break;
		if (art[i] != '\n'&& art[i] != '\t'&& art[i] != ' ')
		{
			j++;
			//ͳ�Ƶ�������������ע������
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



			catToken(ch);
			do
			{
				do
				{
					get();
					if (isNewline(ch))
					{
