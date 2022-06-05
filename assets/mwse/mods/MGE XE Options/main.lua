--[[
    Mod: MGE XE In-game Config
    Author: Hrnchamd
    Version: 1.0
]]--

local gui = require("MGE XE Options.gui")
local i18n = mwse.loadTranslations("MGE XE Options")

local modConfig = {}
function modConfig.onCreate(parent)
	local container = parent:createThinBorder{}
	container.flowDirection = "top_to_bottom"
	container.layoutHeightFraction = 1.0
	container.layoutWidthFraction = 1.0
	container.paddingAllSides = 12

	local header = container:createLabel{text = "MGE XE"}
	header.color = tes3ui.getPalette("header_color")
	header.borderAllSides = 12

	local button = container:createButton{text = i18n("OpenSettings")}
	button.paddingAllSides = 10
	button.paddingBottom = nil

	button:register("mouseClick", function(e)
		-- Check if MGE API is available.
		if mge.render then
			-- Click MCM OK button.
			local ok = parent:getTopLevelMenu():findChild("MWSE:ModConfigMenu_Close")
			if ok then
				ok:triggerEvent("mouseClick")
			end
			-- Hide MenuOptions if in-game.
			local menuOptions = tes3ui.findMenu("MenuOptions")
			if menuOptions and not tes3.onMainMenu() then
				menuOptions.visible = false
			end
			-- Open config.
			local mgeMenu = gui.run()
			-- Show MenuOptions again when window is closed.
			mgeMenu:register("destroy", function()
				local menuOptions = tes3ui.findMenu("MenuOptions")
				if menuOptions then
					menuOptions.visible = true
				end
			end)
		else
			tes3.messageBox{message = i18n("PleaseUpgrade")}
		end
	end)
end

event.register("modConfigReady", function ()
	mwse.registerModConfig("MGE XE", modConfig)
end)


local function onInitialized(mod)
	gui.i18n = i18n
end
event.register("initialized", onInitialized)
