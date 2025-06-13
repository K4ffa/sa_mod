modded class SCR_PlayerController {
	override void OnControlledEntityChanged(IEntity from, IEntity to){
		super.OnControlledEntityChanged(from,to);
		if(Replication.IsServer()){			
			Rpc(RpcDo_OpenAG);
			SCR_CharacterDamageManagerComponent dam = SCR_CharacterDamageManagerComponent.Cast(GetMainEntity().FindComponent(SCR_CharacterDamageManagerComponent));
			if(dam){
				dam.EnableDamageHandling(false);
			}
		}
	}	
	[RplRpc(RplChannel.Reliable, RplRcver.Owner)]
	protected void RpcDo_OpenAG()	{
		if(GetGame().GetPlayerController().HasRole(EPlayerRole.GAME_MASTER)){
			return;
		}
		if(GetGame().GetPlayerController().HasRole(EPlayerRole.ADMINISTRATOR)){
			return;
		}
		if(GetGame().GetPlayerController().HasRole(EPlayerRole.SESSION_ADMINISTRATOR)){
			return;
		}		
	}

	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
	void RpcEnableDams(){
		GetGame().GetCallqueue().CallLater(EnableDmg,3000);
	}
	void EnableDmg(){
		SCR_CharacterDamageManagerComponent dam = SCR_CharacterDamageManagerComponent.Cast(GetMainEntity().FindComponent(SCR_CharacterDamageManagerComponent));
		if(dam){
			dam.EnableDamageHandling(true);
		}
	}
}