static void lzodso_kbd_init(void)
{
	/* SIPO */
	GPIO_SIPOSHR_CLK_DDR |= (1 << GPIO_SIPOSHR_CLK);
	GPIO_SIPOSHR_OUT_DDR |= (1 << GPIO_SIPOSHR_OUT);
	GPIO_SIPOSHR_RST_DDR |= (1 << GPIO_SIPOSHR_RST);
	/* PISO */
	GPIO_PISOSHR_CLK_DDR |= (1 << GPIO_PISOSHR_CLK);
	GPIO_PISOSHR_LOAD_DDR |= (1 << GPIO_PISOSHR_LOAD);
	GPIO_PISOSHR_Q_DDR &= ~(1 << GPIO_PISOSHR_Q);
	/* KCI */
	GPIO_KCI_OUT_DDR |= (1 << GPIO_KCI_OUT);
}

int board_init(void)
{
	/* SYSCLK */
	GPIO_SYSCLK_IN_DDR &= ~(1 << GPIO_SYSCLK_IN);
	/* Keyboard */
	lzodso_kbd_sysclk_init();
	return 0;
}
