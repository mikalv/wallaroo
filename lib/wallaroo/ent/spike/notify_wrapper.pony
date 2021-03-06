/*

Copyright 2017 The Wallaroo Authors.

Licensed as a Wallaroo Enterprise file under the Wallaroo Community
License (the "License"); you may not use this file except in compliance with
the License. You may obtain a copy of the License at

     https://github.com/wallaroolabs/wallaroo/blob/master/LICENSE

*/

use "wallaroo/ent/network"

primitive SpikeWrapper
  fun apply(letter: WallarooOutgoingNetworkActorNotify iso,
    config: SpikeConfig val): WallarooOutgoingNetworkActorNotify iso^
  =>
    var notify: WallarooOutgoingNetworkActorNotify iso = consume letter
    if config.drop then
      notify = DropConnection(config, consume notify)
    end

    consume notify
