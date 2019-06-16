class cAimbot {
public:
	void Run( cUserCmd* Cmd );
private:
	int findTarget( );
	void aimAtTarget( cUserCmd* Cmd );
	void removeInaccuracies( cUserCmd* Cmd );
}; extern cAimbot* Aimbot;