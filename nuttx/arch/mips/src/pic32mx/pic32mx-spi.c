/****************************************************************************
 * arch/mips/src/pic32mx/pic32mx-spi.c
 *
 *   Copyright (C) 2012 Gregory Nutt. All rights reserved.
 *   Author: Gregory Nutt <gnutt@nuttx.org>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name NuttX nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <sys/types.h>
#include <stdint.h>
#include <stdbool.h>
#include <semaphore.h>
#include <errno.h>
#include <debug.h>

#include <arch/board/board.h>
#include <nuttx/arch.h>
#include <nuttx/spi.h>

#include "up_internal.h"
#include "up_arch.h"

#include "chip.h"
#include "pic32mx-internal.h"
#include "pic32mx-spi.h"

#if defined(CONFIG_PIC32MX_SPI1) || defined(CONFIG_PIC32MX_SPI2) || \
    defined(CONFIG_PIC32MX_SPI3) || defined(CONFIG_PIC32MX_SPI4)

/****************************************************************************
 * Definitions
 ****************************************************************************/
/* Enables non-standard debug output from this file */

#ifndef CONFIG_DEBUG
#  undef CONFIG_DEBUG_SPI
#endif

#ifdef CONFIG_DEBUG_SPI
#  define spidbg  lldbg
#  ifdef CONFIG_DEBUG_VERBOSE
#    define spivdbg lldbg
#  else
#    define spivdbg(x...)
#  endif
#else
#  undef CONFIG_DEBUG_VERBOSE
#  define spidbg(x...)
#  define spivdbg(x...)
#endif

/****************************************************************************
 * Private Types
 ****************************************************************************/

/* This structure descibes the state of the SSP driver */

struct pic32mx_dev_s
{
  struct spi_dev_s spidev;     /* Externally visible part of the SPI interface */
  uint32_t         base;       /* SPI register base address */
#ifdef CONFIG_PIC32MX_SPI_INTERRUPTS
  uint8_t          vector;     /* Interrupt vector number(for attaching) */
  uint8_t          eirq;       /* SPI fault interrupt number */
  uint8_t          rxirq;      /* SPI receive done interrupt number */
  uint8_t          txirq;      /* SPI transfer done interrupt number */
#endif
#ifndef CONFIG_SPI_OWNBUS
  sem_t            exclsem;    /* Held while chip is selected for mutual exclusion */
  uint32_t         frequency;  /* Requested clock frequency */
  uint32_t         actual;     /* Actual clock frequency */
  uint8_t          nbits;      /* Width of word in bits (8 to 16) */
  uint8_t          mode;       /* Mode 0,1,2,3 */
#endif
};

/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/
/* Low-level register access */

static uint32_t spi_getreg(FAR struct pic32mx_dev_s *priv,
                  unsigned int offset);
static void     spi_putreg(FAR struct pic32mx_dev_s *priv,
                  unsigned int offset, uint32_t value);

/* SPI methods */

#ifndef CONFIG_SPI_OWNBUS
static int      spi_lock(FAR struct spi_dev_s *dev, bool lock);
#endif
static uint32_t spi_setfrequency(FAR struct spi_dev_s *dev, uint32_t frequency);
static void     spi_setmode(FAR struct spi_dev_s *dev, enum spi_mode_e mode);
static void     spi_setbits(FAR struct spi_dev_s *dev, int nbits);
static uint16_t spi_send(FAR struct spi_dev_s *dev, uint16_t ch);
static void     spi_sndblock(FAR struct spi_dev_s *dev, FAR const void *buffer, size_t nwords);
static void     spi_recvblock(FAR struct spi_dev_s *dev, FAR void *buffer, size_t nwords);

/****************************************************************************
 * Private Data
 ****************************************************************************/

#ifdef CONFIG_PIC32MX_SPI1

static const struct spi_ops_s g_spi1ops =
{
#ifndef CONFIG_SPI_OWNBUS
  .lock              = spi_lock,
#endif
  .select            = pic32mx_spi1select,
  .setfrequency      = spi_setfrequency,
  .setmode           = spi_setmode,
  .setbits           = spi_setbits,
  .status            = pic32mx_spi1status,
#ifdef CONFIG_SPI_CMDDATA
  .cmddata           = pic32mx_spi1cmddata,
#endif
  .send              = spi_send,
  .sndblock          = spi_sndblock,
  .recvblock         = spi_recvblock,
#ifdef CONFIG_SPI_CALLBACK
  .registercallback  = pic32mx_spi1register, /* Provided externally */
#else
  .registercallback  = 0,                    /* Not implemented */
#endif
};

static struct pic32mx_dev_s g_spi1dev =
{
  .spidev            = { &g_spi1ops },
  .base              = PIC32MX_SPI1_K1BASE,
#ifdef CONFIG_PIC32MX_SPI_INTERRUPTS
  .vector            = PIC32MX_IRQ_SPI1,
  .eirq              = PIC32MX_IRQSRC_SPI1E,
  .rxirq             = PIC32MX_IRQSRC_SPI1RX,
  .txirq             = PIC32MX_IRQSRC_SPI1TX,
#endif
};
#endif

#ifdef CONFIG_PIC32MX_SPI2
static const struct spi_ops_s g_spi2ops =
{
#ifndef CONFIG_SPI_OWNBUS
  .lock              = spi_lock,
#endif
  .select            = pic32mx_spi2select,
  .setfrequency      = spi_setfrequency,
  .setmode           = spi_setmode,
  .setbits           = spi_setbits,
  .status            = pic32mx_spi2status,
#ifdef CONFIG_SPI_CMDDATA
  .cmddata           = pic32mx_spi2cmddata,
#endif
  .send              = spi_send,
  .sndblock          = spi_sndblock,
  .recvblock         = spi_recvblock,
#ifdef CONFIG_SPI_CALLBACK
  .registercallback  = pic32mx_spi2register, /* Provided externally */
#else
  .registercallback  = 0,                    /* Not implemented */
#endif
};

static struct pic32mx_dev_s g_spi2dev =
{
  .spidev            = { &g_spi2ops },
  .base              = PIC32MX_SPI2_K1BASE,
#ifdef CONFIG_PIC32MX_SPI_INTERRUPTS
  .vector            = PIC32MX_IRQ_SPI2,
  .eirq              = PIC32MX_IRQSRC_SPI2E,
  .rxirq             = PIC32MX_IRQSRC_SPI2RX,
  .txirq             = PIC32MX_IRQSRC_SPI2TX,
#endif
};
#endif

#ifdef CONFIG_PIC32MX_SPI3
static const struct spi_ops_s g_spi3ops =
{
#ifndef CONFIG_SPI_OWNBUS
  .lock              = spi_lock,
#endif
  .select            = pic32mx_spi3select,
  .setfrequency      = spi_setfrequency,
  .setmode           = spi_setmode,
  .setbits           = spi_setbits,
  .status            = pic32mx_spi3status,
#ifdef CONFIG_SPI_CMDDATA
  .cmddata           = pic32mx_spi3cmddata,
#endif
  .send              = spi_send,
  .sndblock          = spi_sndblock,
  .recvblock         = spi_recvblock,
#ifdef CONFIG_SPI_CALLBACK
  .registercallback  = pic32mx_spi3register, /* Provided externally */
#else
  .registercallback  = 0,                    /* Not implemented */
#endif
};

static struct pic32mx_dev_s g_spi3dev =
{
  .spidev            = { &g_spi3ops },
  .base              = PIC32MX_SPI3_K1BASE,
#ifdef CONFIG_PIC32MX_SPI_INTERRUPTS
  .vector            = PIC32MX_IRQ_SPI4,
  .eirq              = PIC32MX_IRQSRC_SPI3E,
  .rxirq             = PIC32MX_IRQSRC_SPI3RX,
  .txirq             = PIC32MX_IRQSRC_SPI3TX,
#endif
};
#endif

#ifdef CONFIG_PIC32MX_SPI4
static const struct spi_ops_s g_spi4ops =
{
#ifndef CONFIG_SPI_OWNBUS
  .lock              = spi_lock,
#endif
  .select            = pic32mx_spi4select,
  .setfrequency      = spi_setfrequency,
  .setmode           = spi_setmode,
  .setbits           = spi_setbits,
  .status            = pic32mx_spi4status,
#ifdef CONFIG_SPI_CMDDATA
  .cmddata           = pic32mx_spi4cmddata,
#endif
  .send              = spi_send,
  .sndblock          = spi_sndblock,
  .recvblock         = spi_recvblock,
#ifdef CONFIG_SPI_CALLBACK
  .registercallback  = pic32mx_spi4register, /* Provided externally */
#else
  .registercallback  = 0,                    /* Not implemented */
#endif
};

static struct pic32mx_dev_s g_spi4dev =
{
  .spidev            = { &g_spi4ops },
  .base              = PIC32MX_SPI4_K1BASE,
#ifdef CONFIG_PIC32MX_SPI_INTERRUPTS
  .vector            = PIC32MX_IRQ_SPI4,
  .eirq              = PIC32MX_IRQSRC_SPI4E,
  .rxirq             = PIC32MX_IRQSRC_SPI4RX,
  .txirq             = PIC32MX_IRQSRC_SPI4TX,
#endif
};
#endif

/****************************************************************************
 * Public Data
 ****************************************************************************/

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: spi_getreg
 *
 * Description:
 *   Return the contents of one, 32-bit SPI register
 *
 * Input Parameters:
 *   priv   - A pointer to a PIC32MX SPI state structure
 *   offset - Offset from the SPI base address to the register of interest
 *
 * Returned Value:
 *   The current contents of the register
 *
 ****************************************************************************/

static uint32_t spi_getreg(FAR struct pic32mx_dev_s *priv, unsigned int offset)
{
  return getreg32(priv->base + offset);
}

/****************************************************************************
 * Name: spi_getreg
 *
 * Description:
 *   Write a value to one, 32-bit SPI register
 *
 * Input Parameters:
 *   priv   - A pointer to a PIC32MX SPI state structure
 *   offset - Offset from the SPI base address to the register of interest
 *   value  - The value to write to the SPI register
 *
 * Returned Value:
 *   None
 *
 ****************************************************************************/

static void spi_putreg(FAR struct pic32mx_dev_s *priv, unsigned int offset,
                       uint32_t value)
{
  putreg32(value, priv->base + offset);
}

/****************************************************************************
 * Name: spi_lock
 *
 * Description:
 *   On SPI busses where there are multiple devices, it will be necessary to
 *   lock SPI to have exclusive access to the busses for a sequence of
 *   transfers.  The bus should be locked before the chip is selected. After
 *   locking the SPI bus, the caller should then also call the setfrequency,
 *   setbits, and setmode methods to make sure that the SPI is properly
 *   configured for the device.  If the SPI buss is being shared, then it
 *   may have been left in an incompatible state.
 *
 * Input Parameters:
 *   dev  - Device-specific state data
 *   lock - true: Lock spi bus, false: unlock SPI bus
 *
 * Returned Value:
 *   None
 *
 ****************************************************************************/

#ifndef CONFIG_SPI_OWNBUS
static int spi_lock(FAR struct spi_dev_s *dev, bool lock)
{
  FAR struct pic32mx_dev_s *priv = (FAR struct pic32mx_dev_s *)dev;

  if (lock)
    {
      /* Take the semaphore (perhaps waiting) */

      while (sem_wait(&priv->exclsem) != 0)
        {
          /* The only case that an error should occur here is if the wait was awakened
           * by a signal.
           */

          ASSERT(errno == EINTR);
        }
    }
  else
    {
      (void)sem_post(&priv->exclsem);
    }
  return OK;
}
#endif

/****************************************************************************
 * Name: spi_setfrequency
 *
 * Description:
 *   Set the SPI frequency.
 *
 * Input Parameters:
 *   dev -       Device-specific state data
 *   frequency - The SPI frequency requested
 *
 * Returned Value:
 *   Returns the actual frequency selected
 *
 ****************************************************************************/

static uint32_t spi_setfrequency(FAR struct spi_dev_s *dev, uint32_t frequency)
{
  FAR struct pic32mx_dev_s *priv = (FAR struct pic32mx_dev_s *)dev;
  uint32_t divisor;
  uint32_t actual;
  uint32_t regval;

  /* Check if the requested frequency is the same as the frequency selection */

#ifndef CONFIG_SPI_OWNBUS
  if (priv->frequency == frequency)
    {
      /* We are already at this frequency.  Return the actual. */

      return priv->actual;
    }
#endif

  /* Calculate the divisor
   *
   * frequency = BOARD_PBCLOCK / (2 * divisor), or
   * divisor  = (BOARD_PBCLOCK / 2) / frequency
   */

  divisor = (BOARD_PBCLOCK / 2) / frequency;

  /* The a BRG register value is that divisor minus one
   *
   * frequency = BOARD_PBCLOCK /(2 * (BRG + 1)), or
   * BRG       = (BOARD_PBCLOCK / 2) / frequency - 1
   */

  regval = divisor;
  if (regval > 0)
    {
      regval--;
    }

  /* Save the new BRG value */
  
  spi_putreg(priv, PIC32MX_SPI_BRG_OFFSET, regval);

  /* Calculate the new actual frequency"
   *
   * frequency = BOARD_PBCLOCK / (2 * divisor)
   */

  actual = (BOARD_PBCLOCK / 2) / divisor;

  /* Save the frequency setting */

#ifndef CONFIG_SPI_OWNBUS
  priv->frequency = frequency;
  priv->actual    = actual;
#endif

  spidbg("Frequency %d->%d\n", frequency, actual);
  return actual;
}

/****************************************************************************
 * Name: spi_setmode
 *
 * Description:
 *   Set the SPI mode. Optional.  See enum spi_mode_e for mode definitions
 *
 * Input Parameters:
 *   dev -  Device-specific state data
 *   mode - The SPI mode requested
 *
 * Returned Value:
 *   none
 *
 ****************************************************************************/

static void spi_setmode(FAR struct spi_dev_s *dev, enum spi_mode_e mode)
{
  FAR struct pic32mx_dev_s *priv = (FAR struct pic32mx_dev_s *)dev;
  uint32_t regval;

  /* Has the mode changed? */

#ifndef CONFIG_SPI_OWNBUS
  if (mode != priv->mode)
    {
#endif
      /* Yes... Set CR appropriately */

      regval = spi_getreg(priv, PIC32MX_SPI_CON_OFFSET);
      regval &= ~(SPI_CON_CKP|SPI_CON_SMP);

      switch (mode)
        {
        case SPIDEV_MODE0: /* CPOL=0; CPHA=0 */
          break;
 
        case SPIDEV_MODE1: /* CPOL=0; CPHA=1 */
          regval |= SPI_CON_SMP;
          break;
 
        case SPIDEV_MODE2: /* CPOL=1; CPHA=0 */
          regval |= SPI_CON_CKP;
          break;
 
        case SPIDEV_MODE3: /* CPOL=1; CPHA=1 */
          regval |= (SPI_CON_CKP|SPI_CON_SMP);
          break;
 
        default:
          DEBUGASSERT(FALSE);
          return;
        }

      spi_putreg(priv, PIC32MX_SPI_CON_OFFSET, regval);

      /* Save the mode so that subsequent re-configuratins will be faster */

#ifndef CONFIG_SPI_OWNBUS
      priv->mode = mode;
    }
#endif
}

/****************************************************************************
 * Name: spi_setbits
 *
 * Description:
 *   Set the number if bits per word.
 *
 * Input Parameters:
 *   dev -  Device-specific state data
 *   nbits - The number of bits requests
 *
 * Returned Value:
 *   none
 *
 ****************************************************************************/

static void spi_setbits(FAR struct spi_dev_s *dev, int nbits)
{
  FAR struct pic32mx_dev_s *priv = (FAR struct pic32mx_dev_s *)dev;
  uint32_t mode;
  uint32_t regval;

  /* Has the number of bits changed? */

  DEBUGASSERT(priv && nbits > 7 && nbits < 17);
#ifndef CONFIG_SPI_OWNBUS
  if (nbits != priv->nbits)
    {
#endif
      /* Yes... Set the CON register appropriately */

      if (nbits == 8)
        {
          mode = SPI_CON_MODE_8BIT;
        }
      else if (nbits == 16)
        {
          mode = SPI_CON_MODE_8BIT;
        }
      else if (nbits == 32)
        {
          mode = SPI_CON_MODE_8BIT;
        }
      else
        {
          spidbg("Unsupported nbits: %d\n", nbits);
          return;
        }

      regval = spi_getreg(priv, PIC32MX_SPI_CON_OFFSET);
      regval &= ~SPI_CON_MODE_MASK;
      regval |= mode;
      regval = spi_getreg(priv, PIC32MX_SPI_CON_OFFSET);

      /* Save the selection so the subsequence re-configurations will be faster */

#ifndef CONFIG_SPI_OWNBUS
      priv->nbits = nbits;
    }
#endif
}

/****************************************************************************
 * Name: spi_send
 *
 * Description:
 *   Exchange one word on SPI
 *
 * Input Parameters:
 *   dev - Device-specific state data
 *   wd  - The word to send.  the size of the data is determined by the
 *         number of bits selected for the SPI interface.
 *
 * Returned Value:
 *   response
 *
 ****************************************************************************/

static uint16_t spi_send(FAR struct spi_dev_s *dev, uint16_t wd)
{
  FAR struct pic32mx_dev_s *priv = (FAR struct pic32mx_dev_s *)dev;

  /* Write the data to transmitted to the SPI Data Register */

  spi_putreg(priv, PIC32MX_SPI_BUF_OFFSET, (uint32_t)wd);

  /* Wait for the SPITBE bit in the SPI Status Register to be set to 1. The
   * SPITBE bit will be set when the receive buffer is not empty.
   */

 while ((spi_getreg(priv, PIC32MX_SPI_STAT_OFFSET) & SPI_STAT_SPITBE) == 0);

 /* Return the SPI data */

 return (uint16_t)spi_getreg(priv, PIC32MX_SPI_BUF_OFFSET);
}

/*************************************************************************
 * Name: spi_sndblock
 *
 * Description:
 *   Send a block of data on SPI
 *
 * Input Parameters:
 *   dev -    Device-specific state data
 *   buffer - A pointer to the buffer of data to be sent
 *   nwords - the length of data to send from the buffer in number of words.
 *            The wordsize is determined by the number of bits-per-word
 *            selected for the SPI interface.  If nbits <= 8, the data is
 *            packed into uint8_t's; if nbits >8, the data is packed into uint16_t's
 *
 * Returned Value:
 *   None
 *
 ****************************************************************************/

static void spi_sndblock(FAR struct spi_dev_s *dev, FAR const void *buffer, size_t nwords)
{
  FAR struct pic32mx_dev_s *priv = (FAR struct pic32mx_dev_s *)dev;
  FAR uint8_t *ptr = (FAR uint8_t*)buffer;
  uint32_t regval;
  uint8_t data;

  spidbg("nwords: %d\n", nwords);
  while (nwords)
    {
      /* Write the data to transmitted to the SPI Data Register */

      data = *ptr++;
      spi_putreg(priv, PIC32MX_SPI_BUF_OFFSET, (uint32_t)data);

      /* Wait for the SPITBE bit in the SPI Status Register to be set to 1.
       * The SPITBE bit will be set when the receive buffer is not empty.
       */

     while ((spi_getreg(priv, PIC32MX_SPI_STAT_OFFSET) & SPI_STAT_SPITBE) == 0);

     /* Read from the buffer register to clear the status bit */

     regval = spi_getreg(priv, PIC32MX_SPI_BUF_OFFSET);
     nwords--;
    }
}

/****************************************************************************
 * Name: spi_recvblock
 *
 * Description:
 *   Revice a block of data from SPI
 *
 * Input Parameters:
 *   dev -    Device-specific state data
 *   buffer - A pointer to the buffer in which to recieve data
 *   nwords - the length of data that can be received in the buffer in number
 *            of words.  The wordsize is determined by the number of bits-per-word
 *            selected for the SPI interface.  If nbits <= 8, the data is
 *            packed into uint8_t's; if nbits >8, the data is packed into uint16_t's
 *
 * Returned Value:
 *   None
 *
 ****************************************************************************/

static void spi_recvblock(FAR struct spi_dev_s *dev, FAR void *buffer, size_t nwords)
{
  FAR struct pic32mx_dev_s *priv = (FAR struct pic32mx_dev_s *)dev;
  FAR uint8_t *ptr = (FAR uint8_t*)buffer;

  spidbg("nwords: %d\n", nwords);
  while (nwords)
    {
      /* Write some dummy data to the SPI Data Register in order to clock the
       * read data.
       */

      spi_putreg(priv, PIC32MX_SPI_BUF_OFFSET, 0xff);

      /* Wait for the SPITBE bit in the SPI Status Register to be set to 1.
       * The SPITBE bit will be set when the receive buffer is not empty.
       */

     while ((spi_getreg(priv, PIC32MX_SPI_STAT_OFFSET) & SPI_STAT_SPITBE) == 0);

     /* Read the received data from the SPI Data Register */   

     *ptr++ = (uint8_t)spi_getreg(priv, PIC32MX_SPI_BUF_OFFSET);
     nwords--;
    }
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: up_spiinitialize
 *
 * Description:
 *   Initialize the selected SPI port
 *
 * Input Parameter:
 *   Port number (for hardware that has mutiple SPI interfaces)
 *
 * Returned Value:
 *   Valid SPI device structure reference on succcess; a NULL on failure
 *
 ****************************************************************************/

FAR struct spi_dev_s *up_spiinitialize(int port)
{
  FAR struct pic32mx_dev_s *priv;
  irqstate_t flags;
  uint32_t regval;

  /* Select the SPI state structure for this port */

#ifdef CONFIG_PIC32MX_SPI1
  if (port == 1)
    {
      priv = &g_spi1dev;
    }
  else
#endif
#ifdef CONFIG_PIC32MX_SPI2
  if (port == 2)
    {
      priv = &g_spi2dev;
    }
  else
#endif
#ifdef CONFIG_PIC32MX_SPI3
  if (port == 3)
    {
      priv = &g_spi3dev;
    }
  else
#endif
#ifdef CONFIG_PIC32MX_SPI4
  if (port == 4)
    {
      priv = &g_spi4dev;
    }
  else
#endif
   {
     spidbg("Unsuppport port: %d\n", port);
     return NULL;
   }

  /* Disable SPI interrupts */

  flags = irqsave();
#ifdef CONFIG_PIC32MX_SPI_INTERRUPTS
  up_disable_irq(priv->eirq);
  up_disable_irq(priv->txirq);
  up_disable_irq(priv->rxirq);
#endif

  /* Stop and reset the SPI module by clearing the ON bit in the CON register. */

  spi_putreg(priv, PIC32MX_SPI_CON_OFFSET, 0);

  /* Clear the receive buffer by reading from the BUF register */

  regval = spi_getreg(priv, PIC32MX_SPI_BUF_OFFSET);
  
  /* Set the ENHBUF bit if using Enhanced Buffer mode. */

#ifdef CONFIG_PIC32MX_SPI_INTERRUPTS
  /* Attach the interrupt vector */

  ret = irq_attach(priv->vector, spi_interrupt);
  if (ret < 0)
    {
      spidbg("Failed to attach vector: %d port: %d\n", priv->vector, port);
      goto errout;
    }

  /* Enable SPI interrupts */

  up_enable_irq(priv->eirq);
  up_enable_irq(priv->txirq);
  up_enable_irq(priv->rxirq);

  /* Set the interrupt priority */

  ret = up_prioritize_irq(priv->vector, CONFIG_PIC32MX_SPI_PRIORITY)
  if (ret < 0)
    {
      spidbg("up_prioritize_irq failed: %d\n", ret);
      goto errout;
    }
#endif

  /* Select a default frequency of approx. 400KHz */

  spi_setfrequency((FAR struct spi_dev_s *)priv, 400000);

  /* Clear the SPIROV overflow bit (SPIxSTAT:6). */

  spi_putreg(priv, PIC32MX_SPI_STATCLR_OFFSET, SPI_STAT_SPIROV);

  /* Initial settings 8 bit +  master mode + mode 0*/

  regval = (SPI_CON_MSTEN | SPI_CON_MODE_8BIT | SPI_CON_ON);
#ifdef CONFIG_PIC32MX_SPI_INTERRUPTS
  regval |= (SPI_CON_RTXISEL_HALF | SPI_CON_STXISEL_HALF);
#endif
  spi_putreg(priv, PIC32MX_SPI_CON_OFFSET, regval);

  /* Set the initial SPI configuration */

#ifndef CONFIG_SPI_OWNBUS
  priv->nbits = 8;
  priv->mode  = SPIDEV_MODE0;
#endif

  /* Initialize the SPI semaphore that enforces mutually exclusive access */

#ifndef CONFIG_SPI_OWNBUS
  sem_init(&priv->exclsem, 0, 1);
#endif
  irqrestore(flags);
  return &priv->spidev;

#ifdef CONFIG_PIC32MX_SPI_INTERRUPTS
errout:
  irqrestore(flags);
  return NULL;
#endif
}

#endif /* CONFIG_PIC32MX_SPI */
