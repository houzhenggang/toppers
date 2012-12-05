/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2003-2006 by Ryosuke Takeuchi
  *                     GJ Business Division RICOH COMPANY,LTD. JAPAN
 * 
 *  ��L���쌠�҂́C�ȉ��� (1)�`(4) �̏������CFree Software Foundation 
 *  �ɂ���Č��\����Ă��� GNU General Public License �� Version 2 �ɋL
 *  �q����Ă�������𖞂����ꍇ�Ɍ���C�{�\�t�g�E�F�A�i�{�\�t�g�E�F�A
 *  �����ς������̂��܂ށD�ȉ������j���g�p�E�����E���ρE�Ĕz�z�i�ȉ��C
 *  ���p�ƌĂԁj���邱�Ƃ𖳏��ŋ�������D
 *  (1) �{�\�t�g�E�F�A���\�[�X�R�[�h�̌`�ŗ��p����ꍇ�ɂ́C��L�̒���
 *      ���\���C���̗��p��������щ��L�̖��ۏ؋K�肪�C���̂܂܂̌`�Ń\�[
 *      �X�R�[�h���Ɋ܂܂�Ă��邱�ƁD
 *  (2) �{�\�t�g�E�F�A���C���C�u�����`���ȂǁC���̃\�t�g�E�F�A�J���Ɏg
 *      �p�ł���`�ōĔz�z����ꍇ�ɂ́C�Ĕz�z�ɔ����h�L�������g�i���p
 *      �҃}�j���A���Ȃǁj�ɁC��L�̒��쌠�\���C���̗��p��������щ��L
 *      �̖��ۏ؋K����f�ڂ��邱�ƁD
 *  (3) �{�\�t�g�E�F�A���C�@��ɑg�ݍ��ނȂǁC���̃\�t�g�E�F�A�J���Ɏg
 *      �p�ł��Ȃ��`�ōĔz�z����ꍇ�ɂ́C���̂����ꂩ�̏����𖞂�����
 *      �ƁD
 *    (a) �Ĕz�z�ɔ����h�L�������g�i���p�҃}�j���A���Ȃǁj�ɁC��L�̒�
 *        �쌠�\���C���̗��p��������щ��L�̖��ۏ؋K����f�ڂ��邱�ƁD
 *    (b) �Ĕz�z�̌`�Ԃ��C�ʂɒ�߂���@�ɂ���āCTOPPERS�v���W�F�N�g��
 *        �񍐂��邱�ƁD
 *  (4) �{�\�t�g�E�F�A�̗��p�ɂ�蒼�ړI�܂��͊ԐړI�ɐ����邢���Ȃ鑹
 *      �Q������C��L���쌠�҂����TOPPERS�v���W�F�N�g��Ɛӂ��邱�ƁD
 * 
 *  �{�\�t�g�E�F�A�́C���ۏ؂Œ񋟂���Ă�����̂ł���D��L���쌠�҂�
 *  ���TOPPERS�v���W�F�N�g�́C�{�\�t�g�E�F�A�Ɋւ��āC���̓K�p�\����
 *  �܂߂āC�����Ȃ�ۏ؂��s��Ȃ��D�܂��C�{�\�t�g�E�F�A�̗��p�ɂ�蒼
 *  �ړI�܂��͊ԐړI�ɐ����������Ȃ鑹�Q�Ɋւ��Ă��C���̐ӔC�𕉂�Ȃ��D
 * 
 *  @(#) $Id: scanf.c,v 1.2 2009/01/27 12:28:38 roi Exp $
 */

/*
 *	scanf��p�v���O����
 */

#include <stdarg.h>
#include <stdio.h>

typedef	void		*VP;		/* �^����܂�Ȃ����̂ւ̃|�C���^ */
typedef	VP		VP_INT;		/* VP �܂��� INT */

#define	BOOL	int
#define TRUE	1
#define FALSE	0
#define FHALF   0
#define FINT    1
#define FLONG   2

static BOOL is_terminator(char c)
{
	if(c == '\0')
		return TRUE;
	else if(c == '\r' || c == '\n' || c == 0xc)
		return TRUE;
	else
		return FALSE;
}

/*
 *  ������𐔒l�ɕϊ�
 */
static int
convert(VP_INT p, int radix, int padzero, int width, int minus, int (*getsub)(char **p), char ** getbuf, int type)
{
	char	c;
	int		i;
	unsigned long val = 0;
	int count = 0;
	int csign = 0;

	if(width <= 0)
		width = 64;
	c = getsub(getbuf);				/* get first character */
	if(is_terminator((char)c))
		return count;
	if(c < '0' || (c > '9' && c < 'A')
			   || (c > 'Z' && c < 'a') || c > 'z'){
		c = getsub(getbuf);
		if(is_terminator((char)c))
			return count;
	}

	while(c == ' ' || c == '\t'){	/* skip white space */
		c = getsub(getbuf);
		if(is_terminator((char)c))
			return count;
	}

	if(padzero && c == '0'){		/* skip pad zero */
		do{
			c = getsub(getbuf);
			if(is_terminator((char)c))
				return count;
		}while(c == '0');
	}
	for( ; !is_terminator((char)c) ; c = getsub(getbuf), width--){
		if(c == '\t' || c == ' ' || c == ',')
			break;
		if(c == '-' && minus){
			csign = 1;
			width++;
		}
		else if(c >= '0' && c <= '9')
			i = c - '0';
		else if(c >= 'A' && c <= 'Z')
			i = c - 'A' + 10;
		else if(c >= 'a' && c <= 'z')
			i = c - 'a' + 10;
		else
			continue;

		if(i >= radix)
			i = radix - 1;
		val = val * radix + i;
		count = 1;
		if(width <= 1)
			break;
	}
	if(csign)
		val = (unsigned long)((long)val * -1);

	switch(type){
	case FHALF:
		*((unsigned short *)p) = (unsigned short)val;
		break;
	case FLONG:
		*((unsigned long *)p) = (unsigned long)val;
		break;
	default:
		*((unsigned int *)p) = (unsigned int)val;
		break;
	}
	return count;
}


/*
 *  �f�[�^��荞�݃��C�u�����֐�
 */

int _getformat (int (*getsub)(char **p), char ** getbuf, const char * format, va_list ap)
{
	int c;
	int count = 0;
	int	width;
	int	padzero;
	VP_INT	val;
	char *str;

	while ((c = *format++) != '\0') {
		if (c != '%') {
			continue;
		}

		width = padzero = 0;
		c = *format++;
		if (c >= '1' && c <= '9') {
			padzero = 1;
		}
		while (c >= '0' && c <= '9') {
			width = width*10 + c - '0';
			c = *format++;
		}
		switch (c) {
		case 'l':						/* long */
			c = *format++;
			switch (c) {
			case 'd':					/* long 10�i���� */
			case 'i':					/* long 8,10,16�i���� */
				val = (VP_INT) va_arg(ap, VP_INT);
				count += convert(val, 10, padzero, width, 1, getsub, getbuf, FLONG);
				break;
			case 'u':					/* unsigned long 10�i���� */
				val = (VP_INT) va_arg(ap, VP_INT);
				count += convert(val, 10, padzero, width, 0, getsub, getbuf, FLONG);
				break;
			case 'o':					/* unsigned long 8�i���� */
				val = (VP_INT) va_arg(ap, VP_INT);
				count += convert(val, 8, padzero, width, 0, getsub, getbuf, FLONG);
				break;
			case 'x':					/* unsigned long 16�i���� */
				val = (VP_INT) va_arg(ap, VP_INT);
				count += convert(val, 16, padzero, width, 0, getsub, getbuf, FLONG);
				break;
			case 'X':					/* unsigned long �啶��16�i���� */
				val = (VP_INT) va_arg(ap, VP_INT);
				count += convert(val, 16, padzero, width, 0, getsub, getbuf, FLONG);
				break;
			case '\0':
				format--;
				break;
			}
			break;
		case 'h':						/* short */
			c = *format++;
			switch (c) {
			case 'd':					/* short 8�i���� */
			case 'i':					/* short 8,10,16�i���� */
				val = (VP_INT) va_arg(ap, VP_INT);
				count += convert(val, 10, padzero, width, 1, getsub, getbuf, FHALF);
				break;
			case 'u':					/* unsigned short 10�i���� */
				val = (VP_INT) va_arg(ap, VP_INT);
				count += convert(val, 10, padzero, width, 0, getsub, getbuf, FHALF);
				break;
			case 'o':					/* unsigned short 8�i���� */
				val = (VP_INT) va_arg(ap, VP_INT);
				count += convert(val, 8, padzero, width, 0, getsub, getbuf, FHALF);
				break;
			case 'x':					/* unsigned short 16�i���� */
				val = (VP_INT) va_arg(ap, VP_INT);
				count += convert(val, 16, padzero, width, 0, getsub, getbuf, FHALF);
				break;
			case 'X':					/* unsigned short �啶��16�i���� */
				val = (VP_INT) va_arg(ap, VP_INT);
				count += convert(val, 16, padzero, width, 0, getsub, getbuf, FHALF);
				break;
			case '\0':
				format--;
				break;
			}
			break;
		case 'd':						/* int 10�i���� */
		case 'i':						/* int 8,10,16�i���� */
			val = (VP_INT) va_arg(ap, VP_INT);
			count += convert(val, 10, padzero, width, 1, getsub, getbuf, FINT);
			break;
		case 'u':						/* unsigned int 10�i���� */
			val = (VP_INT) va_arg(ap, VP_INT);
			count += convert(val, 10, padzero, width, 0, getsub, getbuf, FINT);
			break;
		case 'o':						/* unsigned int 8�i���� */
			val = (VP_INT) va_arg(ap, VP_INT);
			count += convert(val, 8, padzero, width, 0, getsub, getbuf, FINT);
			break;
		case 'x':						/* unsigned int 16�i���� */
			val = (VP_INT) va_arg(ap, VP_INT);
			count += convert(val, 16, padzero, width, 0, getsub, getbuf, FINT);
			break;
		case 'X':						/* unsigned int �啶��16�i���� */
			val = (VP_INT) va_arg(ap, VP_INT);
			count += convert(val, 16, padzero, width, 0, getsub, getbuf, FINT);
			break;

		case 'c':						/* 1�o�C�g���� */
			str = (char *) va_arg(ap, VP_INT);
			*str = getsub(getbuf);
			count++;
			break;
		case 's':						/* ������ */
			str = (char *) va_arg(ap, VP_INT);
			do{
				c = getsub(getbuf);
				if(c == ' ' || c == '\t')
					break;
				if(is_terminator((char)c))
					break;
				if(width > 0)
					*str++ = c;
				width--;
			}while(c != '\0');
			*str = '\0';
			count++;
			break;
		case '\0':
			format--;
			break;
		default:
			break;
		}
	}
	return count;
}

static int getzi (char ** p)
{
	return getchar();
}

int scanf (const char * format, ...)
{
    va_list args;
    va_start(args, format);
    return (_getformat(getzi, NULL, format, args));
}


