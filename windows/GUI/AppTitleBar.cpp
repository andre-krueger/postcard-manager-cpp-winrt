#include "pch.h"
#include "AppTitleBar.h"

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::GUI::implementation
{
	AppTitleBar::AppTitleBar()
	{
		InitializeComponent();
		auto titleBar = Windows::ApplicationModel::Core::CoreApplication::GetCurrentView().TitleBar();
		titleBar.ExtendViewIntoTitleBar(true);
		titleBar.LayoutMetricsChanged([this, titleBar](winrt::Windows::ApplicationModel::Core::CoreApplicationViewTitleBar, Windows::Foundation::IInspectable) {
			TitleBar().Height(titleBar.Height());
		});
		Window::Current().SetTitleBar(TitleBar());
	}
}
