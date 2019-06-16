#include "Includes.h"

cMenu* Menu;

bool menuInfo::menuActive = false;
static bool gay2;
void cMenu::Initialize( ) {
	ImGuiStyle& Style = ImGui::GetStyle( );
	ImGuiIO& io = ImGui::GetIO( );

	Style.Colors[ ImGuiCol_WindowBg ] = ImColor( 30, 30, 30, 255 );
	Style.Colors[ ImGuiCol_TitleBg ] = ImColor( 60, 60, 60, 255 );
	Style.Colors[ ImGuiCol_TitleBgActive ] = ImColor( 60, 60, 60, 255 );
	Style.Colors[ ImGuiCol_Border ] = ImColor( 0, 0, 0, 255 );
	Style.Colors[ ImGuiCol_BorderShadow ] = ImColor( 0, 0, 0, 0 );
	Style.Colors[ ImGuiCol_SliderGrabActive ] = ImColor( 185, 185, 185, 255 );
	Style.Colors[ ImGuiCol_FrameBgHovered ] = ImColor( 125, 125, 125, 255 );
	Style.Colors[ ImGuiCol_FrameBgActive ] = ImColor( 125, 125, 125, 255 );
	Style.Colors[ ImGuiCol_ChildWindowBg ] = ImColor( 50, 50, 50, 255 );

	Style.Colors[ ImGuiCol_Button ] = ImColor( 70, 70, 70, 255 );
	Style.Colors[ ImGuiCol_ButtonActive ] = ImColor( 90, 90, 90, 255 );
	Style.Colors[ ImGuiCol_ButtonHovered ] = ImColor( 90, 90, 90, 255 );

	Style.Alpha = 1;
	Style.WindowRounding = 0;
	Style.FrameRounding = 0;
	Style.ScrollbarRounding = 0;
}
ImFont* Font;
int currentTab = 0;

void doTabs( ) {
	if ( ImGui::BeginChild( "##Tabs", ImVec2( 60, 0 ), true ) ) {

		if ( ImGui::Button( "Aimbot", ImVec2( 44, 20 ) ) )
			currentTab = 0;

		if ( ImGui::Button( "Visuals", ImVec2( 44, 20 ) ) )
			currentTab = 1;

		if ( ImGui::Button( "Misc", ImVec2( 44, 20 ) ) )
			currentTab = 2;

	}ImGui::EndChild( );
}

void cMenu::Run( ) {
	ImGui::SetNextWindowSize( ImVec2( 425, 350 ) );

	if ( !menuInfo::menuActive )
		return;

	if ( ImGui::Begin( "WeebB0t", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_ShowBorders ) ) {
		doTabs( );

		ImGui::SetCursorPos( ImVec2( 75, 26 ) );

		if ( ImGui::BeginChild( "##Options", ImVec2( 0, 0 ), true ) ) {
			switch ( currentTab ) {
			case 0: {
				ImGui::Checkbox( "Aimbot", &Configuration::Aimbot::aimbotEnabled );
				ImGui::Checkbox( "Auto Aim", &Configuration::Aimbot::autoAim );
				ImGui::Checkbox( "Auto Fire", &Configuration::Aimbot::autoFire );
				ImGui::Checkbox( "Silent Aim", &Configuration::Aimbot::silentAim );
				ImGui::Checkbox( "No Recoil", &Configuration::Aimbot::noRecoil );
				ImGui::SliderInt( "Aim Bone", &Configuration::Aimbot::aimBone, 0, 20, "%.0f" );
			} break;
			case 1: {
				ImGui::Checkbox( "Name", &Configuration::Visuals::Player::Name );
				ImGui::Checkbox( "Box", &Configuration::Visuals::Player::Box );
				ImGui::Checkbox( "Health", &Configuration::Visuals::Player::Health );
				ImGui::Checkbox( "Radar", &Configuration::Visuals::Radar::radarEnabled );
				ImGui::SliderFloat( "Radar Size", &Configuration::Visuals::Radar::radarSize, 100, 1000, "%.0f" );
				ImGui::SliderFloat( "Field Of View", &Configuration::Visuals::View::fieldOfView, 0, 135, "%.0f" );
			}break;
			case 2: {
				ImGui::Checkbox( "Auto Bunnyhop", &Configuration::Misc::Movement::autoBunnyhop );
				ImGui::Checkbox( "Auto Strafe", &Configuration::Misc::Movement::autoStrafe );
				ImGui::Checkbox( "Location Spam", &Configuration::Misc::Spam::locationSpam );
				ImGui::Checkbox( "Radio Spam", &Configuration::Misc::Spam::radioSpam );
				ImGui::SliderFloat( "Radio Spam Delay", &Configuration::Misc::Spam::radioSpamDelay, 0, 1000, "%.0f frames" );
			}break;
			}
		}ImGui::EndChild( );

	}ImGui::End( );
}