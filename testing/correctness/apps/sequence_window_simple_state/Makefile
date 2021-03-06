# include root makefile
ifndef ROOT_MAKEFILE_MK
include ../../../../Makefile
endif

# prevent rules from being evaluated/included multiple times
ifndef $(abspath $(lastword $(MAKEFILE_LIST)))_MK
$(abspath $(lastword $(MAKEFILE_LIST)))_MK := 1

# uncomment to disable generate test related targets in this directory
TEST_TARGET := false

# uncomment to disable generate of PONYC command
PONYC_TARGET := false

# uncomment to disable generate exs related targets (build/test/clean) for elixir sources in this directory
#EXS_TARGET := false

# uncomment to disable generate docker related targets (build/push) for Dockerfile in this directory
#DOCKER_TARGET := false

# uncomment to disable generate recursing into Makefiles of subdirectories
#RECURSE_SUBMAKEFILES := false


SEQUENCE_WINDOW_SIMPLE_STATE_PATH := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

# standard rules generation makefile
include $(rules_mk_path)


# Reuse the validator from sequence_window
build-testing-correctness-apps-sequence_window_simple_state: build-testing-correctness-apps-sequence_window-validator

# This will build three different binaries of sequence_window, but respect PONYCFLAGS passed
# to Make
-include $(subst $(abs_wallaroo_dir)/,,$(SEQUENCE_WINDOW_SIMPLE_STATE_PATH:%/=%))/$(notdir $(abspath $(SEQUENCE_WINDOW_SIMPLE_STATE_PATH:%/=%))).d
$(subst $(abs_wallaroo_dir)/,,$(SEQUENCE_WINDOW_SIMPLE_STATE_PATH:%/=%))/$(notdir $(abspath $(SEQUENCE_WINDOW_SIMPLE_STATE_PATH:%/=%))):
	$(eval original_PONYCFLAGS := $(PONYCFLAGS))
	$(eval PONYCFLAGS := $(original_PONYCFLAGS) -D resilience -D spike -D spiketrace -D validate)
	$(call PONYC,$(abspath $(SEQUENCE_WINDOW_SIMPLE_STATE_PATH:%/=%)))
	mv $(abspath $(SEQUENCE_WINDOW_SIMPLE_STATE_PATH:%/=%))/sequence_window_simple_state $(abspath $(SEQUENCE_WINDOW_SIMPLE_STATE_PATH:%/=%))/sequence_window_simple_state_resilience
	$(eval PONYCFLAGS := $(original_PONYCFLAGS) -D spike -D spiketrace)
	$(call PONYC,$(abspath $(SEQUENCE_WINDOW_SIMPLE_STATE_PATH:%/=%)))
	mv $(abspath $(SEQUENCE_WINDOW_SIMPLE_STATE_PATH:%/=%))/sequence_window_simple_state $(abspath $(SEQUENCE_WINDOW_SIMPLE_STATE_PATH:%/=%))/sequence_window_simple_state_spike
	$(eval PONYCFLAGS := $(original_PONYCFLAGS))
	$(call PONYC,$(abspath $(SEQUENCE_WINDOW_SIMPLE_STATE_PATH:%/=%)))


test-testing-correctness-apps-sequence_window_simple_state: build-testing-correctness-apps-sequence_window_simple_state

test-testing-correctness-apps-sequence_window_simple_state: sequence_window_simple_state_test

sequence_window_simple_state_test:
	cd $(SEQUENCE_WINDOW_SIMPLE_STATE_PATH) && \
	integration_test --sequence-sender '(0,1000]' \
	  --log-level error \
		--command './sequence_window_simple_state' \
		--validation-cmd 'validator -e 1000 -a -i' \
		--output 'received.txt' \
		--giles-mode \
		--workers 2 \
		--batch-size 10 \
		--sink-expect 1000

clean-testing-correctness-apps-sequence_window_simple_state: sequence_window_simple_state_clean

sequence_window_simple_state_clean:
	$(QUIET)rm -fr $(SEQUENCE_WINDOW_SIMPLE_STATE_PATH)/sequence_window_simple_state*

# end of prevent rules from being evaluated/included multiple times
endif
