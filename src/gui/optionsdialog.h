/*
 * Bittorrent Client using Qt and libtorrent.
 * Copyright (C) 2006  Christophe Dumez <chris@qbittorrent.org>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * In addition, as a special exception, the copyright holders give permission to
 * link this program with the OpenSSL project's "OpenSSL" library (or with
 * modified versions of it that use the same license as the "OpenSSL" library),
 * and distribute the linked executables. You must obey the GNU General Public
 * License in all respects for all of the code used other than "OpenSSL".  If you
 * modify file(s), you may extend this exception to your version of the file(s),
 * but you are not obligated to do so. If you do not wish to do so, delete this
 * exception statement from your version.
 */

#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include <QButtonGroup>
#include <QDialog>

class QAbstractButton;
class QCloseEvent;
class QListWidgetItem;
class AdvancedSettings;

// actions on double-click on torrents
enum DoubleClickAction
{
    TOGGLE_PAUSE,
    OPEN_DEST,
    NO_ACTION
};

namespace Net
{
    enum class ProxyType;
}

namespace Ui
{
    class OptionsDialog;
}

class OptionsDialog : public QDialog
{
    Q_OBJECT
    using ThisType = OptionsDialog;

private:
    enum Tabs
    {
        TAB_UI,
        TAB_DOWNLOADS,
        TAB_CONNECTION,
        TAB_SPEED,
        TAB_BITTORRENT,
        TAB_RSS,
        TAB_WEBUI,
        TAB_ADVANCED
    };

public:
    // Constructor / Destructor
    OptionsDialog(QWidget *parent = nullptr);
    ~OptionsDialog();

public slots:
    void showConnectionTab();

private slots:
    void enableForceProxy(bool enable);
    void enableProxy(int index);
    void on_buttonBox_accepted();
    void closeEvent(QCloseEvent *e) override;
    void on_buttonBox_rejected();
    void applySettings(QAbstractButton *button);
    void enableApplyButton();
    void toggleComboRatioLimitAct();
    void changePage(QListWidgetItem *, QListWidgetItem *);
    void loadWindowState();
    void loadSplitterState();
    void saveWindowState() const;
    void handleScanFolderViewSelectionChanged();
    void on_IpFilterRefreshBtn_clicked();
    void handleIPFilterParsed(bool error, int ruleCount);
    void on_banListButton_clicked();
    void on_IPSubnetWhitelistButton_clicked();
    void on_randomButton_clicked();
    void on_addScanFolderButton_clicked();
    void on_removeScanFolderButton_clicked();
    void on_btnWebUiCrt_clicked();
    void on_btnWebUiKey_clicked();
    void on_registerDNSBtn_clicked();
    void setLocale(const QString &localeStr);
    void on_fetchButton_clicked();
    void handlePublicTrackersListDownloadFinished(const QString &url, const QByteArray &data);
    void handlePublicTrackersListDownloadFailed(const QString &url, const QString &error);

private:
    // Methods
    void saveOptions();
    void loadOptions();
    void initializeLanguageCombo();
    static QString languageToLocalizedString(const QLocale &locale);
    // General options
    QString getLocale() const;
#ifndef Q_OS_MAC
    bool systrayIntegration() const;
    bool minimizeToTray() const;
    bool closeToTray() const;
#endif
    bool startMinimized() const;
    bool isSplashScreenDisabled() const;
#ifdef Q_OS_WIN
    bool WinStartup() const;
#endif
    // Downloads
    bool preAllocateAllFiles() const;
    bool useAdditionDialog() const;
    bool addTorrentsInPause() const;
    QString getTorrentExportDir() const;
    QString getFinishedTorrentExportDir() const;
    QString askForExportDir(const QString &currentExportPath);
    int getActionOnDblClOnTorrentDl() const;
    int getActionOnDblClOnTorrentFn() const;
    // Connection options
    int getPort() const;
    bool isUPnPEnabled() const;
    // Bittorrent options
    int getMaxConnecs() const;
    int getMaxConnecsPerTorrent() const;
    int getMaxUploads() const;
    int getMaxUploadsPerTorrent() const;
    bool isDHTEnabled() const;
    bool isLSDEnabled() const;
    int getEncryptionSetting() const;
    qreal getMaxRatio() const;
    int getMaxSeedingMinutes() const;
    // Proxy options
    bool isProxyEnabled() const;
    bool isProxyAuthEnabled() const;
    QString getProxyIp() const;
    unsigned short getProxyPort() const;
    QString getProxyUsername() const;
    QString getProxyPassword() const;
    Net::ProxyType getProxyType() const;
    // IP Filter
    bool isIPFilteringEnabled() const;
    QString getFilter() const;
    bool m_refreshingIpFilter;
    // Queueing system
    bool isQueueingSystemEnabled() const;
    int getMaxActiveDownloads() const;
    int getMaxActiveUploads() const;
    int getMaxActiveTorrents() const;
    bool isWebUiEnabled() const;
    QString webUiUsername() const;
    QString webUiPassword() const;
    // WebUI SSL Cert / key
    bool setSslKey(const QByteArray &key);
    bool setSslCertificate(const QByteArray &cert);
    bool schedTimesOk();
    bool webUIAuthenticationOk();
    bool isAlternativeWebUIPathValid();

    QByteArray m_sslCert, m_sslKey;

    Ui::OptionsDialog *m_ui;
    QAbstractButton *m_applyButton;
    AdvancedSettings *m_advancedSettings;
    QList<QString> m_addedScanDirs;
    QList<QString> m_removedScanDirs;
};

#endif // OPTIONSDIALOG_H
