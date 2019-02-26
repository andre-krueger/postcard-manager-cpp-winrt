#pragma once
#include "App.xaml.g.h"

#include "location_repository.hpp"
#include "database_service.hpp"

namespace winrt::GUI::implementation
{
    struct App : AppT<App>
    {
        App();

        void OnLaunched(Windows::ApplicationModel::Activation::LaunchActivatedEventArgs const&);
        void OnSuspending(IInspectable const&, Windows::ApplicationModel::SuspendingEventArgs const&);
        void OnNavigationFailed(IInspectable const&, Windows::UI::Xaml::Navigation::NavigationFailedEventArgs const&);

        inline static DatabaseService databaseService{ "" };
        inline static LocationRepository LocationRepository{ databaseService };
    };
}
