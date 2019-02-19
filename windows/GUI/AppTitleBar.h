#pragma once

#include "winrt/Windows.UI.Xaml.h"
#include "winrt/Windows.UI.Xaml.Markup.h"
#include "winrt/Windows.UI.Xaml.Interop.h"
#include "AppTitleBar.g.h"

namespace winrt::GUI::implementation
{
	struct AppTitleBar : AppTitleBarT<AppTitleBar>
	{
		AppTitleBar();
	};
}

namespace winrt::GUI::factory_implementation
{
	struct AppTitleBar : AppTitleBarT<AppTitleBar, implementation::AppTitleBar>
	{
	};
}
