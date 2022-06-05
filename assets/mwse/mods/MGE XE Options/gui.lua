local this = {}
local autoSetDistances = true

-- Custom components
local function createPane(menu, id)
	local p = menu:createBlock{id = id}
	p.widthProportional = 1.0
	p.autoHeight = true
	p.flowDirection = tes3.flowDirection.topToBottom
	p.visible = false

	-- Propagate update event to children
	p:registerBefore("update", function(e)
		for i, child in ipairs(e.source.children) do
			child:triggerEvent(e)
		end
	end)
	return p
end

local function showPane(menu, n)
	local e = menu:getContentElement()
	for i=2, #e.children-1 do
		e.children[i].visible = false
	end

	local pane = e.children[n+1]
	pane:triggerEvent("update")
	pane.visible = true
	menu:updateLayout()
end

local function updatePanes(menu)
	local e = menu:getContentElement()
	for i=2, #e.children-1 do
		e.children[i]:triggerEvent("update")
	end
	menu:updateLayout()
end

local function createGroup(parent, id)
	local group = parent:createThinBorder{id = id}
	group.borderAllSides = 8
	group.paddingAllSides = 6
	group.widthProportional = 1.0
	group.autoHeight = true
	group.flowDirection = tes3.flowDirection.topToBottom

	-- Propagate update event to children
	group:registerBefore("update", function(e)
		for i, child in ipairs(e.source.children) do
			child:triggerEvent(e)
		end
	end)
	return group
end

local function createSpacer(parent)
	local element = parent:createBlock()
	element.height = 12
	return element
end

local function createRightAlignedLabel(parent, text, minWidth)
	local element = parent:createBlock()
	element.autoWidth = true
	element.autoHeight = true
	element.minWidth = minWidth

	local label = element:createLabel{text = text}
	label.justifyText = tes3.justifyText.right
	label.wrapText = true
	return label
end

local function createThinButton(parent, text)
	local b = parent:createButton{text = text}
	b.contentPath = "menu_thin_border.nif"
	b.borderAllSides = 0
	b.paddingAllSides = 1
	b.autoWidth = true
	b.autoHeight = true
	b.widthProportional = 1.0
	return b
end

local function createNumberEdit(parent, id, text, getter, setter, delta)
	local block = parent:createBlock{id = id}
	block.widthProportional = 1.0
	block.autoHeight = true
	block.childAlignY = 0.5

	local label = block:createLabel{text = text}
	local valueLabel = createRightAlignedLabel(block, getter(), 60)
	label.minWidth = 250
	valueLabel.borderRight = 10

	local function modify(delta)
		setter(delta)
		valueLabel.text = getter()
		block:getTopLevelMenu():updateLayout()
	end

	local decr = createThinButton(block, '-')
	local incr = createThinButton(block, '+')
	decr.maxWidth = 25
	incr.maxWidth = 25
	decr:register("mouseClick", function(e) modify(-delta) end)
	incr:register("mouseClick", function(e) modify(delta) end)

	block:registerBefore("update", function(e) valueLabel.text = getter() end)
	return block
end

local function createNumberEditx2(parent, id, text, getter1, setter1, delta1, getter2, setter2, delta2)
	local block = createNumberEdit(parent, id, text, getter1, setter1, delta1)
	block.children[1].minWidth = 160

	local valueLabel = createRightAlignedLabel(block, getter2(), 60)
	valueLabel.borderLeft = 20
	valueLabel.borderRight = 10

	local function modify2(delta)
		setter2(delta)
		valueLabel.text = getter2()
		block:getTopLevelMenu():updateLayout()
	end

	local decr = createThinButton(block, '-')
	local incr = createThinButton(block, '+')
	decr.maxWidth = 25
	incr.maxWidth = 25
	decr:register("mouseClick", function(e) modify2(-delta2) end)
	incr:register("mouseClick", function(e) modify2(delta2) end)

	block:registerBefore("update", function(e) valueLabel.text = getter2() end)
	return block
end

local function createCellDistanceEdit(parent, varname, setter, allowNegative)
	local block = parent:createBlock{id = varname}
	block.widthProportional = 1.0
	block.autoHeight = true
	block.childAlignY = 0.5

	local function getter()
		return string.format("%.1f", mge.distantLandRenderConfig[varname])
	end

	local label = block:createLabel{text = this.i18n(varname)}
	label.minWidth = 240
	local valueLabel = createRightAlignedLabel(block, getter(), 40)
	valueLabel.borderRight = 10

	local function modify(varname, delta)
		local value = mge.distantLandRenderConfig[varname] + delta
		if not allowNegative then
			value = math.max(0, value)
		end
		mge.distantLandRenderConfig[varname] = value
		valueLabel.text = getter()
		block:getTopLevelMenu():updateLayout()

		if setter then
			setter(value)
		end
	end

	local decrOne = createThinButton(block, '-1')
	local decrTenth = createThinButton(block, '-')
	local incrTenth = createThinButton(block, '+')
	local incrOne = createThinButton(block, '+1')
	decrOne:register("mouseClick", function(e) modify(varname, -1.0) end)
	decrTenth:register("mouseClick", function(e) modify(varname, -0.1) end)
	incrTenth:register("mouseClick", function(e) modify(varname, 0.1) end)
	incrOne:register("mouseClick", function(e) modify(varname, 1.0) end)

	block:registerBefore("update", function(e) valueLabel.text = getter() end)
	return block
end

local function createFeatureToggle(parent, varname, onChange)
	local block = parent:createBlock{id = varname}
	block.widthProportional = 1.0
	block.autoHeight = true
	block.childAlignY = 0.5

	local label = block:createLabel{text = this.i18n(varname)}
	label.minWidth = 240
	label.borderRight = 10

	local function getter()
		return mge.render[varname] and this.i18n("On") or this.i18n("Off")
	end

	local b = createThinButton(block, getter())
	b:register("mouseClick", function(e)
		local newValue = not mge.render[varname]
		mge.render[varname] = newValue
		b.text = getter()
		if onChange then
			onChange()
		end
	end)

	block:registerBefore("update", function(e) b.text = getter() end)
	return b
end

local function createAutoSetToggle(parent, text, onChange)
	local block = parent:createBlock{}
	block.widthProportional = 1.0
	block.autoHeight = true
	block.childAlignY = 0.5

	local label = block:createLabel{text = text}
	label.minWidth = 270
	label.borderRight = 10

	local function getter()
		return autoSetDistances and this.i18n("On") or this.i18n("Off")
	end

	local b = createThinButton(block, getter())
	b:register("mouseClick", function(e)
		autoSetDistances = not autoSetDistances
		b.text = getter()

		if onChange then
			onChange()
		end
	end)

	block:registerBefore("update", function(e) b.text = getter() end)
	return b
end

local function fixWorldRenderUpdate()
	-- Some updates don't appear until the next frame due to logic ordering.
	-- Temporarily turn off paused world rendering until next frame.
	if mge.render.pauseRenderingInMenus then
		mge.render.pauseRenderingInMenus = false
		timer.delayOneFrame(function() mge.render.pauseRenderingInMenus = true end, timer.real)
	end
end

local function createPPLCycler(parent, text)
	local block = parent:createBlock()
	block.widthProportional = 1.0
	block.autoHeight = true
	block.childAlignY = 0.5

	local label = block:createLabel{text = text}
	label.minWidth = 250

	local function getter()
		local mode = mge.getLightingMode()
		return this.i18n("ppl_" .. mode)
	end

	local b = createThinButton(block, getter())
	b:register("mouseClick", function(e)
		local ppl = mge.getLightingMode()
		if ppl == mge.lightingMode.vertex then
			ppl = mge.lightingMode.perPixel
		elseif ppl == mge.lightingMode.perPixel then
			ppl = mge.lightingMode.perPixelInteriorOnly
		else
			ppl = mge.lightingMode.vertex
		end
		mge.setLightingMode(ppl)
		b.text = getter()

		-- Lighting mode update has one frame latency.
		fixWorldRenderUpdate()
	end)

	block:registerBefore("update", function(e) b.text = getter() end)
	return b
end

local function weatherLabel(weatherID)
	return this.i18n(string.format("Weather%d", weatherID))
end


function this.run()
	local i18n = this.i18n

	-- Close menu if triggered second time
	local menu = tes3ui.findMenu("MenuMGE-XE")
	if menu then
		menu:destroy()
		return
	end

	-- Create menu
	menu = tes3ui.createMenu{id = "MenuMGE-XE", dragFrame = true, loadable = false}
	menu.text = "MGE XE"
	menu.width = 520
	menu.height = 720
	menu.minWidth = 480
	menu.minHeight = 720

	-- Right-align menu position
	menu.positionX = 0.5 * menu.maxWidth - menu.width
	menu.positionY = 0.5 * menu.height + 20

	-- UI creation
	local element
	local pane
	local section

	-- Tab selector
	section = menu:createBlock()
	section.borderAllSides = 8
	section.widthProportional = 1.0
	section.autoHeight = true

	element = createThinButton(section, i18n("TabRendering"))
	element:register("mouseClick", function(e) showPane(menu, 1) end)
	element = createThinButton(section, i18n("TabDistantLand"))
	element:register("mouseClick", function(e) showPane(menu, 2) end)
	element = createThinButton(section, i18n("TabWater"))
	element:register("mouseClick", function(e) showPane(menu, 3) end)
	element = createThinButton(section, i18n("TabWeather"))
	element:register("mouseClick", function(e) showPane(menu, 4) end)
	element = createThinButton(section, i18n("TabLighting"))
	element:register("mouseClick", function(e) showPane(menu, 5) end)

	-- Turn off widthProportional, because the layout does not stabilize when using it
	for i, child in ipairs(section.children) do
		child.widthProportional = nil
	end

	-- Rendering pane
	pane = createPane(menu, "PaneRendering")
	section = createGroup(pane)
	createFeatureToggle(section, "fpsCounter")
	createFeatureToggle(section, "crosshairAutoHide",
		function(newValue)
			-- Make sure crosshair is visible when switching off auto-hide.
			if not newValue then
				tes3.worldController.cursorOff = false
			end
		end)
	createFeatureToggle(section, "pauseRenderingInMenus")

	section = createGroup(pane)
	createNumberEdit(section, nil, i18n("UIScale"),
		function() return string.format("%0.2f", mge.getUIScale()) end,
		function(s)
			s = mge.getUIScale() + s
			s = math.max(0.5, math.min(4.0, s))

			-- On scale change, the menu system partially resets. The menu has to be moved back to where it was after scaling.
			local x, y = menu.positionX, menu.positionY
			mge.setUIScale(s)
			menu.positionX, menu.positionY = x, y
			menu:updateLayout()
		end,
		0.05)

	section = createGroup(pane)
	createNumberEdit(section, nil, i18n("FOV"),
		function() return string.format("%0.1f", mge.camera.fov) end,
		function(x)
			mge.camera.fov = math.max(45.0, mge.camera.fov + x)
			-- FOV updates have one frame latency.
			fixWorldRenderUpdate()
		end,
		1.0)
	createNumberEdit(section, nil, i18n("ThirdPersonCameraX"),
		function() return string.format("%0.1f", mge.camera.thirdPersonOffset.x) end,
		function(x) mge.camera.thirdPersonOffset = mge.camera.thirdPersonOffset + tes3vector3.new(x, 0, 0) end,
		5.0)
	createNumberEdit(section, nil, i18n("ThirdPersonCameraY"),
		function() return string.format("%0.1f", mge.camera.thirdPersonOffset.y) end,
		function(x) mge.camera.thirdPersonOffset = mge.camera.thirdPersonOffset + tes3vector3.new(0, x, 0) end,
		5.0)
	createNumberEdit(section, nil, i18n("ThirdPersonCameraZ"),
		function() return string.format("%0.1f", mge.camera.thirdPersonOffset.z) end,
		function(x) mge.camera.thirdPersonOffset = mge.camera.thirdPersonOffset + tes3vector3.new(0, 0, x) end,
		5.0)

	section = createGroup(pane)
	createFeatureToggle(section, "shaders")
	createNumberEdit(section, nil, i18n("HDRReactionSpeed"),
		function() return string.format("%0.2f sec", mge.shaders.hdrReactionSpeed) end,
		function(x) mge.shaders.hdrReactionSpeed = mge.shaders.hdrReactionSpeed + x end,
		0.1)
	createSpacer(section)
	section:createLabel{text = i18n("ShaderList")}
	element = section:createBlock()
	element.widthProportional = 1.0
	element.autoHeight = true
	element.borderLeft = 30
	element.flowDirection = tes3.flowDirection.topToBottom
	for i, shader in pairs(mge.shaders.list) do
		local shaderText = element:createTextSelect{text = shader.name}
		if not shader.enabled then
			shaderText.widget.state = tes3.uiState.disabled
		end

		shaderText:register("mouseClick", function(e)
			if e.source.widget.state == tes3.uiState.normal then
				e.source.widget.state = tes3.uiState.disabled
				shader.enabled = false
			else
				e.source.widget.state = tes3.uiState.normal
				shader.enabled = true
			end
		end)
	end

	-- Distant land pane
	pane = createPane(menu, "PaneDistantLand")
	section = createGroup(pane)
	createFeatureToggle(section, "distantLand")
	createFeatureToggle(section, "distantStatics")
	createFeatureToggle(section, "grass")
	createFeatureToggle(section, "shadows")

	local function updateAutoDistances()
		if not autoSetDistances then return end

		local section = menu:findChild("RenderDistances")
		local drawDist = mge.distantLandRenderConfig.drawDistance
		local minStaticDist = math.min(drawDist, 4.0)

		mge.distantLandRenderConfig.aboveWaterFogStart = drawDist * 0.24 + 0.4
		mge.distantLandRenderConfig.aboveWaterFogEnd = drawDist

		mge.distantLandRenderConfig.interiorFogStart = 0
		mge.distantLandRenderConfig.interiorFogEnd = drawDist * 0.5 + 0.5

		mge.distantLandRenderConfig.nearStaticEnd = math.max(drawDist * 0.3, minStaticDist)
		mge.distantLandRenderConfig.farStaticEnd = math.max(drawDist * 0.67, minStaticDist)
		mge.distantLandRenderConfig.veryFarStaticEnd = math.max(drawDist * 0.98, minStaticDist)

		-- Update render distance labels.
		section:triggerEvent("update")
	end

	section = createGroup(pane, "RenderDistances")
	createCellDistanceEdit(section, "drawDistance", updateAutoDistances)
	createAutoSetToggle(section, i18n("autoSetDist"), updateAutoDistances)
	createSpacer(section)
	createCellDistanceEdit(section, "nearStaticEnd")
	createCellDistanceEdit(section, "farStaticEnd")
	createCellDistanceEdit(section, "veryFarStaticEnd")
	createSpacer(section)
	createCellDistanceEdit(section, "aboveWaterFogStart", nil, true)
	createCellDistanceEdit(section, "aboveWaterFogEnd")
	createSpacer(section)
	createCellDistanceEdit(section, "belowWaterFogStart", nil, true)
	createCellDistanceEdit(section, "belowWaterFogEnd")
	createSpacer(section)
	createCellDistanceEdit(section, "interiorFogStart", nil, true)
	createCellDistanceEdit(section, "interiorFogEnd")

	section = createGroup(pane)
	createFeatureToggle(section, "exponentialFog",
		function(newValue)
			mge.reloadDistantLand()
		end)
	createFeatureToggle(section, "atmosphericScattering",
		function(newValue)
			mge.reloadDistantLand()
		end)

	-- Water pane
	pane = createPane(menu, "PaneWater")
	section = createGroup(pane)
	createFeatureToggle(section, "reflectiveWater")
	createFeatureToggle(section, "reflectNearStatics")
	createFeatureToggle(section, "reflectInterior")
	createFeatureToggle(section, "reflectSky")
	createFeatureToggle(section, "blurReflections",
		function(newValue)
			mge.reloadDistantLand()
		end)

	section = createGroup(pane)
	createNumberEdit(section, nil, i18n("WaveHeight"),
		function() return string.format("%0.0f", mge.distantLandRenderConfig.waterWaveHeight) end,
		function(x)
			x = mge.distantLandRenderConfig.waterWaveHeight + x
			x = math.max(0, math.min(250, x))
			mge.distantLandRenderConfig.waterWaveHeight = x
		end,
		1.0)
	createNumberEdit(section, nil, i18n("CausticsStrength"),
		function() return string.format("%0.0f%%", mge.distantLandRenderConfig.waterCaustics) end,
		function(x)
			x = mge.distantLandRenderConfig.waterCaustics + x
			x = math.max(0, math.min(100, x))
			mge.distantLandRenderConfig.waterCaustics = x
		end,
		1.0)

	-- Weather pane
	pane = createPane(menu, "PaneWeather")

	section = createGroup(pane)
	section:createLabel{text = i18n("WeatherSectionTitle")}
	createSpacer(section)
	element = section:createBlock()
	element.autoWidth = true
	element.autoHeight = true
	element.borderLeft = 160
	element:createLabel{text = i18n("WeatherDistanceMult")}.minWidth = 135
	element:createLabel{text = i18n("WeatherOffset")}.borderLeft = 10
	for weatherID = 0, 9 do
		createNumberEditx2(section, nil, weatherLabel(weatherID),
			function() return string.format("%0.2f", mge.weather.getDistantFog(weatherID).distance) end,
			function(delta)
				local dlfog = mge.weather.getDistantFog(weatherID)
				dlfog.weather = weatherID
				dlfog.distance = math.max(0, dlfog.distance + delta)
				mge.weather.setDistantFog(dlfog)
			end,
			0.05,
			function() return string.format("%0.0f", mge.weather.getDistantFog(weatherID).offset) end,
			function(delta)
				local dlfog = mge.weather.getDistantFog(weatherID)
				dlfog.weather = weatherID
				dlfog.offset = math.max(0, dlfog.offset + delta)
				mge.weather.setDistantFog(dlfog)
			end,
			5.0)
	end

	section = createGroup(pane)
	section:createLabel{text = i18n("WindSectionTitle")}
	createSpacer(section)
	for weatherID = 0, 9 do
		element = createNumberEdit(section, nil, weatherLabel(weatherID),
			function() return string.format("%0.2f", mge.weather.getWind(weatherID).speed) end,
			function(x)
				local wind = mge.weather.getWind(weatherID)
				wind.speed = math.max(0, wind.speed + x)
				mge.weather.setWind(wind)
			end,
			0.05)
		element.children[1].minWidth = 160
	end


	-- Lighting pane
	pane = createPane(menu, "PaneLighting")
	section = createGroup(pane)
	createPPLCycler(section, i18n("LightingPerPixelMode"))
	element = pane:createLabel{text = i18n("LightingCaveat")}
	element.wrapText = true
	element.borderLeft = 10
	element.borderRight = 10
	element.minHeight = 45

	section = createGroup(pane)
	section:createLabel{text = i18n("LightingSectionTitle")}
	createSpacer(section)

	element = section:createBlock()
	element.autoWidth = true
	element.autoHeight = true
	element.borderLeft = 190
	element:createLabel{text = i18n("LightingSun")}.minWidth = 90
	element:createLabel{text = i18n("LightingAmbient")}
	for weatherID = 0, 9 do
		createNumberEditx2(section, nil, weatherLabel(weatherID),
			function() return string.format("%0.2f", mge.weather.getPerPixelLighting(weatherID).sun) end,
			function(delta)
				local ppl = mge.weather.getPerPixelLighting(weatherID)
				ppl.weather = weatherID
				ppl.sun = math.max(0, ppl.sun + delta)
				mge.weather.setPerPixelLighting(ppl)
			end,
			0.05,
			function() return string.format("%0.2f", mge.weather.getPerPixelLighting(weatherID).ambient) end,
			function(delta)
				local ppl = mge.weather.getPerPixelLighting(weatherID)
				ppl.weather = weatherID
				ppl.ambient = math.max(0, ppl.ambient + delta)
				mge.weather.setPerPixelLighting(ppl)
			end,
			0.05)
	end

	section = menu:createBlock()
	section.widthProportional = 1.0
	section.heightProportional = 1.0
	section.childAlignY = 1.0
	section.autoHeight = true

	-- Bottom bar. Save, load, close.
	element = section:createButton{text = i18n("Save")}
	element:register("mouseClick", function(e)
		mge.saveConfig()
		tes3.messageBox{message = i18n("MsgSaved")}
	end)
	element = section:createButton{text = i18n("Load")}
	element:register("mouseClick", function(e)
		local x, y = menu.positionX, menu.positionY

		mge.loadConfig()
		tes3.messageBox{message = i18n("MsgLoaded")}
		updatePanes(menu)

		-- On scale change, the menu system partially resets. The menu has to be moved back to where it was after scaling.
		menu.positionX, menu.positionY = x, y
		menu:updateLayout()
	end)
	element = section:createBlock()
	element.widthProportional = 1.0
	element.autoHeight = true
	element.childAlignX = 1.0
	element:createButton{text = i18n("Close")}
	element:register("mouseClick", function(e) menu:destroy() end)

	-- Run layout twice to iron out use of proportional sizing on multiple branches.
	showPane(menu, 1)
	menu:updateLayout()
	menu:updateLayout()

	return menu
end

return this
