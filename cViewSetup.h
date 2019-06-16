// https://raw.githubusercontent.com/ValveSoftware/source-sdk-2013/master/sp/src/public/view_shared.h

enum clearFlagsT
{
	VIEW_CLEAR_COLOR = 0x1,
	VIEW_CLEAR_DEPTH = 0x2,
	VIEW_CLEAR_FULL_TARGET = 0x4,
	VIEW_NO_DRAW = 0x8,
	VIEW_CLEAR_OBEY_STENCIL = 0x10,
	VIEW_CLEAR_STENCIL = 0x20,
};

enum stereoEyeT
{
	STEREO_EYE_MONO = 0,
	STEREO_EYE_LEFT = 1,
	STEREO_EYE_RIGHT = 2,
	STEREO_EYE_MAX = 3,
};

class cViewSetup
{
public:
	cViewSetup( )
	{
		aspectRatio = 0.0f;
		renderToSubrectOfLargerScreen = false;
		doBloomAndToneMapping = true;
		Ortho = false;
		offCenter = false;
		cacheFullSceneState = false;
		//		m_bUseExplicitViewVector = false;
		viewToProjectionOverride = false;
		stereoEye = STEREO_EYE_MONO;
	}

	int			x;
	int			unscaledX;
	int			y;
	int			unscaledY;
	int			Width;
	int			unscaledWidth;
	int			height;
	stereoEyeT  stereoEye;
	int			unscaledHeight;
	bool		Ortho;
	float		orthoLeft;
	float		orthoTop;
	float		orthoRight;
	float		orthoBottom;
	float		Fov;
	float		fovViewmodel;
	Vector		Origin;
	Vector		Angles;
	float		Near;
	float		Far;
	float		nearViewmodel;
	float		farViewmodel;
	bool		renderToSubrectOfLargerScreen;
	float		aspectRatio;
	bool		offCenter;
	float		offCenterTop;
	float		offCenterBottom;
	float		offCenterLeft;
	float		offCenterRight;
	bool		doBloomAndToneMapping;
	bool		cacheFullSceneState;
	bool        viewToProjectionOverride;
	byte		viewToProjection;
};