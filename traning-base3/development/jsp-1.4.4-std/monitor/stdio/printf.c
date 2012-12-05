/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2003-2005 by Ryosuke Takeuchi
  *                     GJ Business Division RICOH COMPANY,LTD. JAPAN
 * 
 *  �嵭����Ԥϡ��ʲ��� (1)��(4) �ξ�狼��Free Software Foundation 
 *  �ˤ�äƸ�ɽ����Ƥ��� GNU General Public License �� Version 2 �˵�
 *  �Ҥ���Ƥ���������������˸¤ꡤ�ܥ��եȥ��������ܥ��եȥ�����
 *  ����Ѥ�����Τ�ޤࡥ�ʲ�Ʊ���ˤ���ѡ�ʣ�������ѡ������ۡʰʲ���
 *  ���ѤȸƤ֡ˤ��뤳�Ȥ�̵���ǵ������롥
 *  (1) �ܥ��եȥ������򥽡��������ɤη������Ѥ�����ˤϡ��嵭������
 *      ��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ��꤬�����Τޤޤη��ǥ���
 *      ����������˴ޤޤ�Ƥ��뤳�ȡ�
 *  (2) �ܥ��եȥ������򡤥饤�֥������ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *      �ѤǤ�����Ǻ����ۤ�����ˤϡ������ۤ�ȼ���ɥ�����ȡ�����
 *      �ԥޥ˥奢��ʤɡˤˡ��嵭�����ɽ�����������Ѿ�浪��Ӳ���
 *      ��̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *  (3) �ܥ��եȥ������򡤵�����Ȥ߹���ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *      �ѤǤ��ʤ����Ǻ����ۤ�����ˤϡ����Τ����줫�ξ�����������
 *      �ȡ�
 *    (a) �����ۤ�ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭����
 *        �ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *    (b) �����ۤη��֤��̤�������ˡ�ˤ�äơ�TOPPERS�ץ������Ȥ�
 *        ��𤹤뤳�ȡ�
 *  (4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
 *      ������⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ����դ��뤳�ȡ�
 * 
 *  �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ�
 *  ���TOPPERS�ץ������Ȥϡ��ܥ��եȥ������˴ؤ��ơ�����Ŭ�Ѳ�ǽ����
 *  �ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥ��եȥ����������Ѥˤ��ľ
 *  ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤������Ǥ�����ʤ���
 * 
 *  @(#) $Id: printf.c,v 1.6 2008/03/16 09:01:38 roi Exp $
 */

/*
 *	printf���ѥץ����
 */

#include <itron.h>
#include <stdarg.h>
#include <stdio.h>

/*
 *  ���ͤ�ʸ������Ѵ�
 */
static int
convert(unsigned long val, int radix, const char *radchar, int width, int minus, int padzero,
        void (*putsub)(char c, char **p), char ** putbuf)
{
	char	buf[12];
	int	i, j;
	int count = 0;

	i = 0;
	do {
		buf[i++] = radchar[val % radix];
		val /= radix;
	} while (val != 0);

	width -= minus;
	if (minus > 0 && padzero > 0) {
		putsub('-', putbuf);
		count++;
	}
	for (j = i; j < width; j++) {
		putsub((char)(padzero > 0 ? '0' : ' '), putbuf);
		count++;
	}
	if (minus > 0 && padzero <= 0) {
		putsub('-', putbuf);
		count++;
	}
	while (i > 0) {
		putsub(buf[--i], putbuf);
		count++;
	}
	return count;
}

/*
 *  ������ե����ޥå��ѥ饤�֥��ؿ�
 */
static char const raddec[] = "0123456789";
static char const radhex[] = "0123456789abcdef";
static char const radHEX[] = "0123456789ABCDEF";

int _setformat (void (*putsub)(char c, char **p), char ** putbuf, const char * format, va_list ap)
{
	int	c;
	int count = 0;
	int	width;
	int	padzero;
	long	val;
	char const	*str;

	while ((c = *format++) != '\0') {
		if (c != '%') {
			putsub((char) c, putbuf);
			count++;
			continue;
		}

		width = padzero = 0;
		if ((c = *format++) == '0') {
			padzero = 1;
			c = *format++;
		}
		while ('0' <= c && c <= '9') {
			width = width*10 + c - '0';
			c = *format++;
		}
		switch (c) {
		case 'l':						/* long */
			c = *format++;
			switch (c) {
			case 'd':					/* long 10������ */
			case 'i':					/* long 8,10,16������ */
				val = (long) va_arg(ap, long);
				if (val >= 0)
					count += convert(val, 10, raddec, width, 0, padzero, putsub, putbuf);
				else
					count += convert(-val, 10, raddec, width, 1, padzero, putsub, putbuf);
				break;
			case 'u':					/* unsigned long 10������ */
				val = (long) va_arg(ap, unsigned long);
				count += convert(val, 10, raddec, width, 0, padzero, putsub, putbuf);
				break;
			case 'o':					/* unsigned long 8������ */
				val = (long) va_arg(ap, unsigned long);
				count += convert(val, 8, raddec, width, 0, padzero, putsub, putbuf);
				break;
			case 'x':					/* unsigned long 16������ */
				val = (long) va_arg(ap, unsigned long);
				count += convert(val, 16, radhex, width, 0, padzero, putsub, putbuf);
				break;
			case 'X':					/* unsigned long ��ʸ��16������ */
				val = (long) va_arg(ap, unsigned long);
				count += convert(val, 16, radHEX, width, 0, padzero, putsub, putbuf);
				break;
			case '\0':
				format--;
				break;
			}
			break;

		case 'h':						/* short */
			c = *format++;
			switch (c) {
			case 'd':					/* short 8������ */
			case 'i':					/* short 8,10,16������ */
				val = (long) ((short)va_arg(ap, int));
				if (val >= 0)
					count += convert(val, 10, raddec, width, 0, padzero, putsub, putbuf);
				else
					count += convert(-val, 10, raddec, width, 1, padzero, putsub, putbuf);
				break;
			case 'u':					/* unsigned short 10������ */
				val = (long) ((unsigned short)va_arg(ap, unsigned int));
				count += convert(val, 10, raddec, width, 0, padzero, putsub, putbuf);
				break;
			case 'o':					/* unsigned short 8������ */
				val = (long) ((unsigned short)va_arg(ap, unsigned int));
				count += convert(val, 8, raddec, width, 0, padzero, putsub, putbuf);
				break;
			case 'x':					/* unsigned short 16������ */
				val = (long) ((unsigned short)va_arg(ap, unsigned int));
				count += convert(val, 16, radhex, width, 0, padzero, putsub, putbuf);
				break;
			case 'X':					/* unsigned short ��ʸ��16������ */
				val = (long) ((unsigned short)va_arg(ap, unsigned int));
				count += convert(val, 16, radHEX, width, 0, padzero, putsub, putbuf);
				break;
			case '\0':
				format--;
				break;
			}
			break;
		case 'd':						/* int 10������ */
		case 'i':						/* int 8,10,16������ */
			val = (long) va_arg(ap, int);
			if (val >= 0)
				count += convert(val, 10, raddec, width, 0, padzero, putsub, putbuf);
			else
				count += convert(-val, 10, raddec, width, 1, padzero, putsub, putbuf);
			break;
		case 'u':						/* unsigned int 10������ */
			val = (long) va_arg(ap, unsigned int);
			count += convert(val, 10, raddec, width, 0, padzero, putsub, putbuf);
			break;
		case 'o':						/* unsigned int 8������ */
			val = (long) va_arg(ap, unsigned int);
			count += convert(val, 8, raddec, width, 0, padzero, putsub, putbuf);
			break;
		case 'x':						/* unsigned int 16������ */
			val = (long) va_arg(ap, unsigned int);
			count += convert(val, 16, radhex, width, 0, padzero, putsub, putbuf);
			break;
		case 'X':						/* unsigned int ��ʸ��16������ */
			val = (long) va_arg(ap, unsigned int);
			count += convert(val, 16, radHEX, width, 0, padzero, putsub, putbuf);
			break;

		case 'c':						/* 1�Х���ʸ�� */
			c = (int) va_arg(ap, unsigned int);
			putsub((char)(int)c, putbuf);
			count++;
			break;
		case 's':						/* ʸ���� */
			str = (char const *) va_arg(ap, VP_INT);
			while ((c = *str++) != '\0') {
				putsub((char) c, putbuf);
				count++;
				width--;
			}
			while(width > 0){
				putsub(' ', putbuf);
				count++;
				width--;
			}
			break;
		case '%':
			putsub('%', putbuf);
			count++;
			break;
		case '\0':
			format--;
			break;
		}
	}
	return count;
}

static void putzi (char c, char ** p)
{
    putchar(c);
}

int printf (const char * format, ...)
{
    va_list args;
    va_start(args, format);
    return (_setformat(putzi, NULL, format, args));
}

