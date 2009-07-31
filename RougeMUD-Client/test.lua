function PrintTable(t, n)
	n = n or 0
	local a = 0
	local tab = ""
	while a < n do
		tab = tab.."    "
		a = a+1
	end
	Print(tab.."{")
	for k,v in pairs(t) do
		if type(v) == "table" and t ~= _G then
			Print(tab.."    "..(type(k) == "string" and '["'..tostring(k)..'"]' or '['..tostring(k)..']').." =")
			PrintTable(v, n+1)
		else
			Print(tab.."    "..(type(k) == "string" and '["'..tostring(k)..'"]' or '['..tostring(k)..']').." = "..(type(v) == "string" and '"'..tostring(v)..'"' or tostring(v))..",")
		end
	end
	Print(tab.."} "..tostring(t)..',')
end

Events =
{
	UI_LOAD = function()
	end,
	UI_STEP = function()
	end,
	UI_QUIT = function()
	end
}

function OnEvent(event)
	local func = Events[event] or function() end
	func()
	--Print(event)
end

local f = CreateFrame("image")
local r = CreateFrame("region")

f:SetX(10);
f:SetY(10);
f:SetW(10);
f:SetH(10);

--[[f:SetAnchor("TOPLEFT", r, "TOPRIGHT", 10, 10)
f:SetAnchor("TOPRIGHT", f, "TOPRIGHT", 0, 0)]]
f:SetEventHandler(OnEvent)
f:NoticeEvent("UI_LOAD", "UI_QUIT", "UI_STEP")

PrintTable(GetRegistry()["EVENT"])
Print("------------------------")
PrintTable(GetRegistry()["OBJECT"])
Print("------------------------")
PrintTable(f)
Print("------------------------")
PrintTable(r)
Print("------------------------")
PrintTable(GlobalRegion)
