#
# Makefile for the kernel tpm device drivers.
#
obj-$(CONFIG_TCG_TPM) += tpm.o
obj-$(CONFIG_TCG_TPM) += tpm_bios.o
ifdef CONFIG_ACPI
	tpm_bios-objs += tpm_eventlog.o tpm_acpi.o
endif
ifdef CONFIG_TCG_IBMVTPM
	tpm_bios-objs += tpm_eventlog.o tpm_of.o
endif
obj-$(CONFIG_TCG_TIS) += tpm_tis.o
obj-$(CONFIG_TCG_NSC) += tpm_nsc.o
obj-$(CONFIG_TCG_ATMEL) += tpm_atmel.o
obj-$(CONFIG_TCG_INFINEON) += tpm_infineon.o
obj-$(CONFIG_TCG_IBMVTPM) += tpm_ibmvtpm.o
