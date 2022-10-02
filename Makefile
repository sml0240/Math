# Alternative GNU Make workspace makefile autogenerated by Premake

ifndef config
  config=debug
endif

ifndef verbose
  SILENT = @
endif

ifeq ($(config),debug)
  Tests_config = debug

else ifeq ($(config),release)
  Tests_config = release

else
  $(error "invalid configuration $(config)")
endif

PROJECTS := Tests

.PHONY: all clean help $(PROJECTS) 

all: $(PROJECTS)

Tests:
ifneq (,$(Tests_config))
	@echo "==== Building Tests ($(Tests_config)) ===="
	@${MAKE} --no-print-directory -C . -f Tests.make config=$(Tests_config)
endif

clean:
	@${MAKE} --no-print-directory -C . -f Tests.make clean

help:
	@echo "Usage: make [config=name] [target]"
	@echo ""
	@echo "CONFIGURATIONS:"
	@echo "  debug"
	@echo "  release"
	@echo ""
	@echo "TARGETS:"
	@echo "   all (default)"
	@echo "   clean"
	@echo "   Tests"
	@echo ""
	@echo "For more information, see https://github.com/premake/premake-core/wiki"