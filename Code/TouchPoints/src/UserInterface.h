#pragma once
#include "Brush.h"
#include "Illustrator.h"
#include "DeviceHandler.h"
#include "TouchKeyboard.h"
#include "MenuLayer.h"

namespace touchpoints { namespace ui
{
	struct UserInterface
	{
	public:
		UserInterface();
		UserInterface(int mWindowWidth, int mWindowHeight, drawing::Brush* brush, 
			drawing::Illustrator* mIllustrator, devices::DeviceHandler* mDeviceHandler, 
			drawing::SymmetryLine* symmetryLine, std::shared_ptr<gl::Fbo> fbo,
			std::vector<std::shared_ptr<gl::Fbo>>* fboLayerList, std::vector<float>* fboLayerAlpha);
		void modeRectangle();
		void modeCircle();
		void modeTriangle();
		void modeLine();
		void drawUi();
		bool inInteractiveUi(float x, float y, uint32_t id);
		Color getBackgroundColor();
		void setModeChangeFlag();
		void UserInterface::changeBackgroundColor(Color background);
		void clearLayers();
		bool getUiFboFlag();
		void changeModeButtons(bool x);
		void toggleUiFlag();
		bool getUiFlag();
		bool isBackgroundTransparent();
		std::shared_ptr<gl::Fbo> getTransparentBackground();
		bool getFps();
		inline void ToggleFps() { FPS = !FPS; }
		//UI Setup does all the drawing that cannot be done inside a libcinder 'setup' call, such as drawing to Framebuffers.
		void uiSetup();
		void drawDeviceButtonsFbo();
		void drawBrushButtonsFbo();
		void drawShapesButtonsFbo();

		//setter for resize() in TouchPointsApp
		void setUIResize(int mWindowWidth, int mWindowHeight, drawing::Brush* brush, drawing::Illustrator* mIllustrator, std::shared_ptr<gl::Fbo> fbo, std::vector<std::shared_ptr<gl::Fbo>>* fboLayerList);
		//setter and getter for mode button
		void setModeButtons(bool sModeButtons);
		bool getModeButtons();


		void slideButtons(cinder::app::TouchEvent::Touch touch);
		float getLayerAlpha(int layerNumber);
		void incrementBackground();
		void endButtonPress(cinder::app::TouchEvent::Touch touch);
	private:
		void initializeMenuLayer();
		void initializeTopLeftMenu();
		void initializeBottomRightMenu();
		multimap<int, shared_ptr<Menu>> createColorPickerMenu() const;
		multimap<int, shared_ptr<Menu>> createShapePickerMenu() const;
		multimap<int, shared_ptr<Menu>> createBrushPickerMenu() const;
		multimap<int, shared_ptr<Menu>> createLayerVisualizationMenu() const;
		multimap<int, shared_ptr<drawing::TouchShape>> createSymmetryMenuShapes() const;
		multimap<int, shared_ptr<drawing::TouchShape>> createSymmetryDropdownShapes() const;
		multimap<int, shared_ptr<drawing::TouchShape>> createBottomRightMenuShapes() const;
		multimap<int, shared_ptr<Menu>> createBottomRightComposingMenus() const;
		shared_ptr<Menu> createDeviceModeButtonMenu() const;
		shared_ptr<Menu> createSettingsButtonMenu() const;
		shared_ptr<Menu> createShapeDisplayMenu() const;
		multimap<int, shared_ptr<Menu>> UserInterface::createSettingsButtonComposingMenus() const;
		multimap<int, shared_ptr<Menu>> UserInterface::createDevicesModeButtonComposingMenus() const;
		//multimap<int, shared_ptr<Menu>> create
		drawing::Brush* mBrush;
		drawing::Illustrator* illustrator;
		devices::DeviceHandler* deviceHandler;
		drawing::SymmetryLine* symmetryLine;
		TouchKeyboard keyboard;

		//Rectf boundingRect;

		//Frame Buffers for the UI. Mostly Fbo's that held button Draw calls.
		std::shared_ptr<gl::Fbo> uiFbo;
		std::shared_ptr<gl::Fbo> modeButtonsFbo;
		std::shared_ptr<gl::Fbo> brushButtonsFbo;
		std::shared_ptr<gl::Fbo> deviceButtonsFbo;
		std::shared_ptr<gl::Fbo> shapeButtonsFbo;
		std::shared_ptr<gl::Fbo> colorButtonsFbo;
		std::shared_ptr<gl::Fbo> settingsButtonsFbo;
		//Stores the 'Checkerboard pattern for background'
		std::shared_ptr<gl::Fbo> transparentBackgroundFbo; //can remove after finishing BRMenuHandler

		MenuLayer menuLayer;
		shared_ptr<Menu> topLeftMenu;
		shared_ptr<Menu> bottomRightMenu;

		int windowWidth;
		int windowHeight;

		int uiOutlineSize = 5;

		//Mode Flags
		bool modeChangeFlag;
		bool leapRunning;
		bool eyeXRunning;
		bool uiFboFlag;
		bool modeButtons;
		bool brushButtons;
		bool colorButtons;
		bool shapeButtons;
		bool deviceButtons;
		bool layerVisualization;
		bool uiFlag;
		bool undoFlag;
		bool transparentBackground;
		bool FPS = false;
		bool settingsButtons = false;

		std::vector<std::shared_ptr<gl::Fbo>>* layerList;

		std::vector<float>* layerAlpha;
		list<Color> backgroundList;
		Color backgroundColor;
	};
}}
